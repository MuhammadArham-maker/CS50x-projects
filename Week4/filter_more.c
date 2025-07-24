// "Sorry" i forgot to read the insturction carefully i thought it was written submit this version
// if comfortable and this version if more comfortable like the earlier ones but in this one it was
// written to submit one.

#include "helpers.h"
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // GX grid
    const int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    // Gy grid
    const int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Copying the original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Rows
    for (int i = 0; i < height; i++)
    {
        // Columns
        for (int j = 0; j < width; j++)
        {
            // Variables to store sum of RGB

            // For Gx (horizontal)
            int Gx_redsum = 0;
            int Gx_greensum = 0;
            int Gx_bluesum = 0;

            // For Gy (vertical)
            int Gy_redsum = 0;
            int Gy_greensum = 0;
            int Gy_bluesum = 0;

            // Looping 3x3 grids
            // Rows
            for (int di = -1; di <= 1; di++)
            {
                // Columns
                for (int dj = -1; dj <= 1; dj++)
                {
                    // Actual index number of the grids
                    int ni = i + di;
                    int nj = j + dj;

                    // Got the 3x3 grid pixels
                    // Checking bounds
                    if (ni >= 0 && nj >= 0 && ni < height && nj < width)
                    {
                        // For X i.e horizontal check
                        Gx_redsum += copy[ni][nj].rgbtRed * Gx[di + 1][dj + 1];
                        Gx_greensum += copy[ni][nj].rgbtGreen * Gx[di + 1][dj + 1];
                        Gx_bluesum += copy[ni][nj].rgbtBlue * Gx[di + 1][dj + 1];

                        // For Y i.e vertical check
                        Gy_redsum += copy[ni][nj].rgbtRed * Gy[di + 1][dj + 1];
                        Gy_greensum += copy[ni][nj].rgbtGreen * Gy[di + 1][dj + 1];
                        Gy_bluesum += copy[ni][nj].rgbtBlue * Gy[di + 1][dj + 1];
                    }
                }
            }
            // Updating the pixels
            image[i][j].rgbtRed =
                round(fmin(255.0, (sqrt((Gx_redsum * Gx_redsum) + (Gy_redsum * Gy_redsum)))));
            image[i][j].rgbtGreen = round(
                fmin(255.0, (sqrt((Gx_greensum * Gx_greensum) + (Gy_greensum * Gy_greensum)))));
            image[i][j].rgbtBlue =
                round(fmin(255.0, (sqrt((Gx_bluesum * Gx_bluesum) + (Gy_bluesum * Gy_bluesum)))));
        }
    }
}
