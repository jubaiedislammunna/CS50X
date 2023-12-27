#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// JPEG
//
// first 3 bytes: 0xff 0xd8 0xff
//
// last bytes: 0xe0 0xe1 0xe2 ... 0xef
//
//

#define BLOCK_SIZE 512

// typedef to make code more readable
typedef uint8_t byte;

// writes block to file
void writeToFile(byte b[], FILE *f)
{
    fwrite(b, sizeof(byte) * BLOCK_SIZE, 1, f);
}

int main(int argc, char *argv[])
{

    // checks
    if (argc != 2)
    {
        fprintf(stderr, "correct usage: recover card");
        return 1;
    }

    // i/o files
    FILE *fImage = fopen(argv[1], "r");
    FILE *oImage;

    if (fImage == NULL)
    {
        fclose(fImage);
        fprintf(stderr, "error: cannot open forensic image");
        return 2;
    }

    // this is checking whether i already found a jpg
    bool foundJpeg = true;

    int jcount = 0;

    byte c[4] = {0xff, 0xd8, 0xff, 0xe0};
    byte c2[4] = {0xff, 0xd8, 0xff, 0xe1};

    byte b[BLOCK_SIZE];

    // loop through the forensic image
    while (fread(b, sizeof(byte) * BLOCK_SIZE, 1, fImage) > 0)
    {

        // find beginning of JPEG
        if (memcmp(c, b, 4) == 0 || memcmp(c2, b, 4) == 0)
        {
            // open a new JPEG
            char name[8];
            sprintf(name, "%03d.jpg", jcount);

            if (foundJpeg)
            {
                oImage = fopen(name, "w");
                writeToFile(b, oImage);
                foundJpeg = false;
            }
            if (!foundJpeg)
            {
                fclose(oImage);
                oImage = fopen(name, "w");
                writeToFile(b, oImage);
                jcount++;
            }
        }
        else
        {
            // write 512 bytes until new JPEG is found
            if (!foundJpeg)
            {
                writeToFile(b, oImage);
            }
        }
    }

    if (oImage)
        fclose(oImage);

    fclose(fImage);

    return 0;
}
