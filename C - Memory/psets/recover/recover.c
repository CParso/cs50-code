#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Defining BYTE and BLOCK_SIZE for clarity
typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check for the correct number of arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // Open memory card
    FILE *input = fopen(argv[1], "r");

    // Check if the file opened without issues
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // If there were no issues proceed
    else
    {
        // Define buffer for first fread
        BYTE buffer[BLOCK_SIZE];

        // Initialise a counter for naming the jpeg's
        int file_count = 0;

        // Declare the output file
        FILE *image = NULL;

        // Declare the array for the name to store the jpeg as
        char filename[8];

        // Repeat if the size of memory being read is 512 bytes
        while (fread(&buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
        {
            // If the header matches a jpeg
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // If the image already has information stored within then close it
                if (image != NULL)
                {
                    fclose(image);
                }
                // Create a new string to name the new image as
                sprintf(filename, "%03i.jpg", file_count);

                // Open the new image file
                image = fopen(filename, "w");

                // Increase the jpeg number
                file_count++;
            }
            // If the image file has been opened
            if (image != NULL)
            {
                // Write 512 bytes to it from the original file
                fwrite(&buffer, 1, BLOCK_SIZE, image);
            }
        }
        // Close both files
        fclose(input);
        fclose(image);

        return 0;
    }
}
