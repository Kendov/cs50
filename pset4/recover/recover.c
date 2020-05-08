#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define BUFFER_SIZE 512
#define FILE_NAME_SIZE 8

bool checkHeader(uint8_t buffer[]);
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    //open memory card
    FILE *file = fopen(argv[1], "r");

    //check if file exists
    if (file == NULL)
    {
        printf("File: \"%s\" not found");
        return 1;
    }



    FILE *outFile;
    uint8_t buffer[BUFFER_SIZE];
    bool firstJpegFounded = false;
    int jpegAmount = 0;
    char fileName[FILE_NAME_SIZE];


    //Repeat until end of card
    while (fread(buffer, 1, sizeof(buffer), file) == BUFFER_SIZE)
    {
        if (checkHeader(buffer))
        {
            //check if a jpg has already been found, if true, close and open a new one
            if (!firstJpegFounded)
            {
                sprintf(fileName, "%03i.jpg", jpegAmount++);
                outFile = fopen(fileName, "a");
            }
            else
            {
                sprintf(fileName, "%03i.jpg", jpegAmount++);
                fclose(outFile);
                outFile = fopen(fileName, "a");
            }
            firstJpegFounded = true;
            fwrite(buffer, 1, sizeof(buffer), outFile);
        }
        else
        {
            //check if already found a jpg file
            if (firstJpegFounded)
            {
                //keepWriting
                fwrite(buffer, 1, sizeof(buffer), outFile);
            }
        }
    }
    fclose(outFile);
    fclose(file);

}

//check if is a jpg header
bool checkHeader(uint8_t buffer[])
{
    //shift one bit on each true if statement
    uint8_t output = 1;
    if (buffer[0] == 0xff)
    {
        output = output << 1;
    }
    if (buffer[1] == 0xd8)
    {
        output = output << 1;
    }
    if (buffer[2] == 0xff)
    {
        output = output << 1;
    }
    if ((buffer[3] & 0xf0) == 0xe0)
    {
        output = output << 1;
    }

    //if pass all if statements, the value will be 16
    return output == 16 ? true : false;
}
