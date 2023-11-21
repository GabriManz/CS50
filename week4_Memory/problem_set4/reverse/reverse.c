#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("File %s could not be found.\n", argv[1]);
        return 1;
    }

    // Read header
    WAVHEADER buffer;
    fread(&buffer, sizeof(buffer), 1, input);

    // Check file header end pointer
    int header_end = ftell(input) - 1;

    // Use check_format to ensure WAV format
    if (!check_format(buffer))
    {
        printf("Input is not a valid WAV file.\n");
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("File %s could not be found.\n", argv[2]);
        return 1;
    }

    // Write header to file
    fwrite(&buffer, sizeof(buffer), 1, output);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(buffer);

    // Set the input file pointer to the final record
    fseek(input, -block_size, SEEK_END);

    // Write reversed audio to file
    int *data_buffer = NULL;
    while (ftell(input) >= header_end)
    {
        data_buffer = malloc(block_size);
        fread(data_buffer, block_size, 1, input);
        fwrite(data_buffer, block_size, 1, output);
        fseek(input, -2 * block_size, SEEK_CUR);
    }

    // Free memory and close opened files
    free(data_buffer);
    fclose(input);
    fclose(output);

    return 0;
}

int check_format(WAVHEADER header)
{
    BYTE *format = header.format;
    return format[0] == 'W' && format[1] == 'A' && format[2] == 'V' && format[3] == 'E';
}

int get_block_size(WAVHEADER header)
{
    int size = header.numChannels * (header.bitsPerSample / 8);
    return size;
}
