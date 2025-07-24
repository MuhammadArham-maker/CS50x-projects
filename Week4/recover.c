#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

// Function definition
bool is_jpeg(uint8_t buffer[BLOCK_SIZE]);

int main(int argc, char *argv[])
{
    // Checking for CLA
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    // Opening the Memory card
    FILE *inptr = fopen(argv[1], "rb");

    // Check if file opened correctly
    if (inptr == NULL)
    {
        printf("Couldn't open the file\n");
        return 1;
    }

    // Initializing the files and pointers
    FILE *outptr = NULL;
    int file_count = 0;
    char filename[8];

    // Create a buffer to store 512 bytes
    uint8_t buffer[BLOCK_SIZE];

    // Start Reading the file
    while (fread(buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        // Checks for a jpeg file start
        if (is_jpeg(buffer))
        {
            // Close previous file if open
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // Start of a new .jpeg file

            // Generate file names like "000.jpg", ....
            sprintf(filename, "%03i.jpg", file_count);

            // Open the file for Writing
            outptr = fopen(filename, "wb");
            // Check if file opened correctly
            if (outptr == NULL)
            {
                printf("Couldn't create %s\n", filename);
                return 2;
            }
            file_count++;
        }
        // Writing in the file
        if (outptr != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
    }
    // Close if any remaining files are open
    if (outptr != NULL)
    {
        fclose(outptr);
    }

    fclose(inptr);
    return 0;
}

// Returns True for jpeg file
bool is_jpeg(uint8_t buffer[BLOCK_SIZE])
{
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0);
}
