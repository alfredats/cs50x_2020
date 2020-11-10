#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./ recover image\n");
        return 1;
    }
    
    // Generate a pointer to the address where image is stored in memory
    FILE *instream = fopen(argv[1], "r");

    if (instream == NULL)
    {
        printf("No image mounted\n");
        return 1;
    }
    
    // 1 block = 512 bytes as defined
    BYTE *block = malloc(sizeof(BYTE) * 512);
    FILE *outstream = NULL;
    int file_count = 0;

    // fread returns 0 at EOF or error, so this works
    while (fread(block, sizeof(BYTE) * 512, 1, instream))
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff &&
            block[3] >= 0xe0 && block[3] <= 0xef)
        {
            if (outstream != NULL)
            {
                // close the previous stream if a new file is encountered
                fclose(outstream);
            }

            char filename[10];
            sprintf(filename, "%03i.jpg", file_count);
            file_count += 1;

            outstream = fopen(filename, "w");
            fwrite(block, sizeof(BYTE) * 512, 1, outstream);
        }
        else
        {
            // If the first image has not been initialized, there is 
            // no need to dump data into the IO stream
            if (outstream == NULL)
            {
                continue;
            }

            fwrite(block, sizeof(BYTE) * 512, 1, outstream);
        }
        
    }

    free(block);
    fclose(instream);
    fclose(outstream);

    return 0;
}
