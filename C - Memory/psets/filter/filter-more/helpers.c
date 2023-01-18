#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel
        for (int j = 0; j < width; j++)
        {
            // Assign RGB values to floats so they can be correctly passed to round function
            float b = image[i][j].rgbtBlue;
            float g = image[i][j].rgbtGreen;
            float r = image[i][j].rgbtRed;

            // Calculate the average and then round it
            int average = round((b + g + r) / 3);

            // Assign RGB values to the average
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel in the LEFT half of the image
        for (int j = 0; j < width / 2; j++)
        {
            // Swap them with the mirroring pixel
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /* Initialise a duplicate image so that
     * alterations can be made without affecting
     * future calculations */
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel
        for (int j = 0; j < width; j++)
        {
            // Sums for each colour
            float sum_blue = 0;
            float sum_green = 0;
            float sum_red = 0;

            // Total to be passed to find the average
            int counter = 0;

            // Find the sum of colours in given pixel looping from -1 to +1 on each row and column
            for (int l = -1; l < 2; l++)
            {
                for (int k = -1; k < 2; k++)
                {
                    // Checks if the current pixel exceeds the maximum or minimum
                    // For rows
                    if (i + l >= height || i + l < 0)
                    {
                        continue;
                    }
                    // For columns
                    if (j + k >= width || j + k < 0)
                    {
                        continue;
                    }
                    // Update the sums with the value
                    sum_blue += copy[i + l][j + k].rgbtBlue;
                    sum_green += copy[i + l][j + k].rgbtGreen;
                    sum_red += copy[i + l][j + k].rgbtRed;
                    counter++;
                }
            }
            // Update the final image with the averaged values
            image[i][j].rgbtBlue = round(sum_blue / counter);
            image[i][j].rgbtGreen = round(sum_green / counter);
            image[i][j].rgbtRed = round(sum_red / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    /* Initialise a duplicate image so that
     * alterations can be made without affecting
     * future calculations */
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Setup kernel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel
        for (int j = 0; j < width; j++)
        {
            // Initialise variables for Gx and Gy calculations
            float Gx_blue = 0;
            float Gx_green = 0;
            float Gx_red = 0;
            float Gy_blue = 0;
            float Gy_green = 0;
            float Gy_red = 0;

            // For each adjacent pixel from -1 to +1 rows and columns
            for (int l = -1; l < 2; l++)
            {
                for (int k = -1; k < 2; k++)
                {
                    // Checks if the current pixel exceeds the maximum or minimum
                    // For rows
                    if (i + l >= height || i + l < 0)
                    {
                        continue;
                    }
                    // For columns
                    if (j + k >= width || j + k < 0)
                    {
                        continue;
                    }

                    /* Perform calculations by taking the current pixel
                    and multiplying it by the corresponding Gx/Gy value
                    for each colour in the pixel */
                    Gx_blue += copy[i + l][j + k].rgbtBlue * Gx[l + 1][k + 1];
                    Gx_green += copy[i + l][j + k].rgbtGreen * Gx[l + 1][k + 1];
                    Gx_red += copy[i + l][j + k].rgbtRed * Gx[l + 1][k + 1];
                    Gy_blue += copy[i + l][j + k].rgbtBlue * Gy[l + 1][k + 1];
                    Gy_green += copy[i + l][j + k].rgbtGreen * Gy[l + 1][k + 1];
                    Gy_red += copy[i + l][j + k].rgbtRed * Gy[l + 1][k + 1];
                }
            }
            // Combine the Gx and Gy values for each colour by squaring, adding, finding the square root and then rounding
            int blue = round(sqrt((Gx_blue * Gx_blue) + (Gy_blue * Gy_blue)));
            int green = round(sqrt((Gx_green * Gx_green) + (Gy_green * Gy_green)));
            int red = round(sqrt((Gx_red * Gx_red) + (Gy_red * Gy_red)));

            // If any of the resulting values exceed the cap of 255 reset them to the cap
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (red > 255)
            {
                red = 255;
            }

            // Update the colours of the final image
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtRed = red;
        }
    }
    return;
}
