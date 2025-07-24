#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Each Row
    for (int i = 0; i < height; i++)
    {
        // Each Column
        for (int j = 0; j < width; j++)
        {
            // Pointing to the pixel one by one
            RGBTRIPLE *pixel = &image[i][j];
            // Calculating the avg
            int avg = round((pixel->rgbtRed + pixel->rgbtGreen + pixel->rgbtBlue) / 3.0);
            // Updating the new value in each pixel
            pixel->rgbtRed = pixel->rgbtGreen = pixel->rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Row
    for (int i = 0; i < height; i++)
    {
        // Column
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];
            int sepiaRed = round(0.393 * (pixel->rgbtRed) + 0.769 * (pixel->rgbtGreen) +
                                 0.189 * (pixel->rgbtBlue));
            int sepiaGreen = round(0.349 * (pixel->rgbtRed) + 0.686 * (pixel->rgbtGreen) +
                                   0.168 * (pixel->rgbtBlue));
            int sepiaBlue = round(0.272 * (pixel->rgbtRed) + 0.534 * (pixel->rgbtGreen) +
                                  0.131 * (pixel->rgbtBlue));
            // Return the smallest i.e caps the value till 255
            pixel->rgbtRed = fmin(255, sepiaRed);
            pixel->rgbtGreen = fmin(255, sepiaGreen);
            pixel->rgbtBlue = fmin(255, sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Row
    for (int i = 0; i < height; i++)
    {
        // Column
        for (int j = 0; j < (width / 2); j++)
        {
            // Storing first pixel in a temproray variable and swaping
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Making a copy of original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // For every pixel:
    // Rows
    for (int i = 0; i < height; i++)
    {
        // Columns
        for (int j = 0; j < width; j++)
        {
            // Variables to store the sum of RGB & count
            int redsum = 0;
            int greensum = 0;
            int bluesum = 0;
            int count = 0;

            // Loop over 3x3 grid surrounding each pixel
            // Row
            for (int di = -1; di <= 1; di++)
            {
                // column
                for (int dj = -1; dj <= 1; dj++)
                {
                    // Actual Row index of the grid
                    int ni = i + di;
                    // Actual Column index of the grid
                    int nj = j + dj;

                    // Checking for bounds
                    if (ni >= 0 && nj >= 0 && ni < height && nj < width)
                    {
                        redsum += copy[ni][nj].rgbtRed;
                        greensum += copy[ni][nj].rgbtGreen;
                        bluesum += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Update the calculated new average value in the RGBTRIPLETS
            image[i][j].rgbtRed = round((float) redsum / count);
            image[i][j].rgbtGreen = round((float) greensum / count);
            image[i][j].rgbtBlue = round((float) bluesum / count);
        }
    }
}
