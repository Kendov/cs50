#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            //get the average color of the 3 channels
            int color = round((float)(image[x][y].rgbtRed + image[x][y].rgbtBlue + image[x][y].rgbtGreen) / 3);

            //set the new values
            image[x][y].rgbtRed = color;
            image[x][y].rgbtGreen = color;
            image[x][y].rgbtBlue = color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            //make the calculation for sepia filter
            int colorRed = round(
                               (0.393 * (float)image[x][y].rgbtRed) +
                               (0.769 * (float)image[x][y].rgbtGreen) +
                               (0.189 * (float)image[x][y].rgbtBlue));
            int colorGreen = round(
                                 (0.349 * (float)image[x][y].rgbtRed) +
                                 (0.686 * (float)image[x][y].rgbtGreen) +
                                 (0.168 * (float)image[x][y].rgbtBlue));
            int colorBlue = round(
                                (0.272 * (float)image[x][y].rgbtRed) +
                                (0.534 * (float)image[x][y].rgbtGreen) +
                                (0.131 * (float)image[x][y].rgbtBlue));

            //clamp the value between 0 and 255
            colorRed = (colorRed > 255 ? 255 : colorRed < 0 ? 0 : colorRed);
            colorGreen = (colorGreen > 255 ? 255 : colorGreen < 0 ? 0 : colorGreen);
            colorBlue = (colorBlue > 255 ? 255 : colorBlue < 0 ? 0 : colorBlue);

            //set the new values
            image[x][y].rgbtRed = colorRed;
            image[x][y].rgbtGreen = colorGreen;
            image[x][y].rgbtBlue = colorBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //store half the image size
    int wid = floor((float)width / 2);
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < wid; y++)
        {
            //swap the values
            image[x][y].rgbtRed ^= image[x][width - 1 - y].rgbtRed;
            image[x][width - 1 - y].rgbtRed ^= image[x][y].rgbtRed;
            image[x][y].rgbtRed ^= image[x][width - 1 - y].rgbtRed;

            image[x][y].rgbtGreen ^= image[x][width - 1 - y].rgbtGreen;
            image[x][width - 1 - y].rgbtGreen ^= image[x][y].rgbtGreen;
            image[x][y].rgbtGreen ^= image[x][width - 1 - y].rgbtGreen;

            image[x][y].rgbtBlue ^= image[x][width - 1 - y].rgbtBlue;
            image[x][width - 1 - y].rgbtBlue ^= image[x][y].rgbtBlue;
            image[x][y].rgbtBlue ^= image[x][width - 1 - y].rgbtBlue;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurImage[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {

            int numOfPixels = 0;
            int red = 0;
            int green = 0;
            int blue = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int k = -1; k <= 1; k++)
                {
                    //check if is not out of bound
                    if ((x + i >= 0 && x + i < height) && (y + k >= 0 && y + k < width))
                    {
                        red += image[x + i][y + k].rgbtRed;
                        green += image[x + i][y + k].rgbtGreen;
                        blue += image[x + i][y + k].rgbtBlue;
                        numOfPixels++;
                    }
                }
            }


            //set new values with the average of each color channel
            blurImage[x][y].rgbtRed = round((float)red / numOfPixels);
            blurImage[x][y].rgbtGreen = round((float)green / numOfPixels);
            blurImage[x][y].rgbtBlue = round((float)blue / numOfPixels);

        }

    }

    //add blur image to output image
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = blurImage[x][y];
        }
    }
    return;
}
