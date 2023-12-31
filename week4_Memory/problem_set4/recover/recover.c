#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512
#define FILENAME_MEM 8

// Define SOI_0 as the first byte of a JPEG Start of Image marker
#define SOI_0 0xFF

bool is_jpeg_header(uint8_t header[BLOCK_SIZE]);

int main(int argc, char *argv[])
{
    // Check for proper command line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    bool first_jpg = true;
    char filename[FILENAME_MEM];
    int count = 0;
    FILE *output = NULL;

    // Iterate through all the blocks until the end of file
    while (fread(buffer, BLOCK_SIZE, 1, input))
    {
        // If valid header, start writing jpg
        if (is_jpeg_header(buffer))
        {
            if (!first_jpg)
            {
                fclose(output);
            }
            sprintf(filename, "%03i.jpg", count++);
            output = fopen(filename, "w");
            if (output == NULL)
            {
                return 1;
            }
            fwrite(buffer, BLOCK_SIZE, 1, output);
            first_jpg = false;
        }
        // If not valid header and not first jpeg, continue writing to previous jpeg
        else if (!first_jpg)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }
    }
    fclose(output);

    return 0;
}

// Returns true if and only if we have specified JPEG header
bool is_jpeg_header(uint8_t header[BLOCK_SIZE])
{
    return (header[0] == SOI_0 &&
            header[1] == 0xD8 &&  // SOI_1
            header[2] == 0xFF &&  // APPN
            ((header[3] & 0xF0) == 0xE0));
}
