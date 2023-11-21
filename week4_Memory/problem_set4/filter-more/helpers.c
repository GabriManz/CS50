#include "helpers.h"
#include <math.h>
#include <stdlib.h>

int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //for each pixel, calculate the average of Red, Green, and Blue Values
            BYTE temp = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            //set each of RGB Values to average
            image[i][j].rgbtBlue = temp;
            image[i][j].rgbtGreen = temp;
            image[i][j].rgbtRed = temp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *img = malloc(width * sizeof(RGBTRIPLE));
    if (img == NULL)
    {
        return;
    }

    // Reflect horizontally
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[(width - 1) - j].rgbtRed = image[i][j].rgbtRed;
            img[(width - 1) - j].rgbtGreen = image[i][j].rgbtGreen;
            img[(width - 1) - j].rgbtBlue = image[i][j].rgbtBlue;
        }

        // Copy the reflected pixels back to the original image
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = img[j].rgbtRed;
            image[i][j].rgbtGreen = img[j].rgbtGreen;
            image[i][j].rgbtBlue = img[j].rgbtBlue;
        }
    }

    free(img);

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for the temporary array t
    RGBTRIPLE (*t)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Loop through each pixel in the image
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int tr = 0, tg = 0, tb = 0;
            int n = 0;

            // Iterate over a 3x3 neighborhood around the current pixel
            for (int i = -1; i <= 1; ++i)
            {
                if (x + i >= 0 && x + i < height)
                {
                    for (int j = -1; j <= 1; ++j)
                    {
                        if (y + j >= 0 && y + j < width)
                        {
                            tr += image[x + i][y + j].rgbtRed;
                            tg += image[x + i][y + j].rgbtGreen;
                            tb += image[x + i][y + j].rgbtBlue;
                            n++;
                        }
                    }
                }
            }

            // Calculate the average color values
            float r = tr * 1.0 / n;
            float g = tg * 1.0 / n;
            float b = tb * 1.0 / n;

            // Store the result in the temporary array t
            t[x][y].rgbtRed = (int)round(r);
            t[x][y].rgbtGreen = (int)round(g);
            t[x][y].rgbtBlue = (int)round(b);
        }
    }

    // Copy the values from the temporary array t back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = t[i][j].rgbtRed;
            image[i][j].rgbtGreen = t[i][j].rgbtGreen;
            image[i][j].rgbtBlue = t[i][j].rgbtBlue;
        }
    }

    // Free the allocated memory for the temporary array t
    free(t);
    return;
}

// Detect edges using Sobel operators
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary array to store the updated image
    RGBTRIPLE (*temp_image)[width] = malloc(height * sizeof(RGBTRIPLE[width]));
    if (temp_image == NULL)
    {
    return;
    }

    // Apply Sobel operators to detect edges
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            // Apply Sobel operators
            int gx_red = Gx[0][0] * image[i - 1][j - 1].rgbtRed + Gx[0][1] * image[i - 1][j].rgbtRed + Gx[0][2] * image[i - 1][j + 1].rgbtRed +
                         Gx[2][0] * image[i + 1][j - 1].rgbtRed + Gx[2][1] * image[i + 1][j].rgbtRed + Gx[2][2] * image[i + 1][j + 1].rgbtRed;
            int gx_green = Gx[0][0] * image[i - 1][j - 1].rgbtGreen + Gx[0][1] * image[i - 1][j].rgbtGreen + Gx[0][2] * image[i - 1][j + 1].rgbtGreen +
                           Gx[2][0] * image[i + 1][j - 1].rgbtGreen + Gx[2][1] * image[i + 1][j].rgbtGreen + Gx[2][2] * image[i + 1][j + 1].rgbtGreen;
            int gx_blue = Gx[0][0] * image[i - 1][j - 1].rgbtBlue + Gx[0][1] * image[i - 1][j].rgbtBlue + Gx[0][2] * image[i - 1][j + 1].rgbtBlue +
                          Gx[2][0] * image[i + 1][j - 1].rgbtBlue + Gx[2][1] * image[i + 1][j].rgbtBlue + Gx[2][2] * image[i + 1][j + 1].rgbtBlue;

            int gy_red = Gy[0][0] * image[i - 1][j - 1].rgbtRed + Gy[0][2] * image[i - 1][j + 1].rgbtRed +
                         Gy[1][0] * image[i][j - 1].rgbtRed + Gy[1][2] * image[i][j + 1].rgbtRed +
                         Gy[2][0] * image[i + 1][j - 1].rgbtRed + Gy[2][2] * image[i + 1][j + 1].rgbtRed;
            int gy_green = Gy[0][0] * image[i - 1][j - 1].rgbtGreen + Gy[0][2] * image[i - 1][j + 1].rgbtGreen +
                           Gy[1][0] * image[i][j - 1].rgbtGreen + Gy[1][2] * image[i][j + 1].rgbtGreen +
                           Gy[2][0] * image[i + 1][j - 1].rgbtGreen + Gy[2][2] * image[i + 1][j + 1].rgbtGreen;
            int gy_blue = Gy[0][0] * image[i - 1][j - 1].rgbtBlue + Gy[0][2] * image[i - 1][j + 1].rgbtBlue +
                          Gy[1][0] * image[i][j - 1].rgbtBlue + Gy[1][2] * image[i][j + 1].rgbtBlue +
                          Gy[2][0] * image[i + 1][j - 1].rgbtBlue + Gy[2][2] * image[i + 1][j + 1].rgbtBlue;

            // Combine the results of the Sobel operators
            int new_red = (int)round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int new_green = (int)round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int new_blue = (int)round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            // Cap the values to 255 to ensure they are within the valid range
            new_red = (new_red > 255) ? 255 : new_red;
            new_green = (new_green > 255) ? 255 : new_green;
            new_blue = (new_blue > 255) ? 255 : new_blue;

            // Update the pixel in the temporary array
            temp_image[i][j].rgbtRed = new_red;
            temp_image[i][j].rgbtGreen = new_green;
            temp_image[i][j].rgbtBlue = new_blue;
        }
    }

    // Copy the values from the temporary array back to the original image
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtRed = temp_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp_image[i][j].rgbtBlue;
        }
    }

    // Free the allocated memory for the temporary array
    free(temp_image);
}


