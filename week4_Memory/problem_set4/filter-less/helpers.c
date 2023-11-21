#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average;
            average = round(((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3));
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Check for values exceeding 255
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
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

