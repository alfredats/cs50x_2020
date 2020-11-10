#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void swap(uint8_t *left, uint8_t *right)
{
    uint8_t tmp = *left;
    *left = *right;
    *right = tmp;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned int pixR = image[i][j].rgbtRed;
            unsigned int pixG = image[i][j].rgbtGreen;
            unsigned int pixB = image[i][j].rgbtBlue;
            unsigned int pixRGBavg = round((double)(pixR + pixG + pixB) / 3);

            image[i][j].rgbtRed = pixRGBavg;
            image[i][j].rgbtBlue = (uint8_t) pixRGBavg;
            image[i][j].rgbtGreen = (uint8_t) pixRGBavg;
            
        }
    }
    return;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double pixR = (double) image[i][j].rgbtRed;
            double pixG = (double) image[i][j].rgbtGreen;
            double pixB = (double) image[i][j].rgbtBlue;

            double sepiaR = .393 *  pixR  +  .769 *  pixG + .189 *  pixB;
            double sepiaG = .349 *  pixR  +  .686 *  pixG + .168 *  pixB;
            double sepiaB = .272 *  pixR  +  .534 *  pixG + .131 *  pixB;
       
            image[i][j].rgbtRed = (uint8_t) round(fmin(255,  sepiaR));
            image[i][j].rgbtGreen = (uint8_t) round(fmin(255,  sepiaG));
            image[i][j].rgbtBlue = (uint8_t) round(fmin(255,  sepiaB));
        
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // divide width by 2, recall that integer division is automatically floored
    int num_swaps = width / 2;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < num_swaps; j++)
        {
            // Gotta physically swap dem address
            swap(&image[i][j].rgbtRed,  &image[i][width - 1 - j].rgbtRed);
            swap(&image[i][j].rgbtGreen,  &image[i][width - 1 - j].rgbtGreen);
            swap(&image[i][j].rgbtBlue,  &image[i][width - 1 - j].rgbtBlue);
        } 
    }

    return;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //cheeky cheeky. to do a "blur" we need a duplicate image to update,   otherwise
    //updates on earlier pixels will affect the calculations of later ones.
     
    RGBTRIPLE(*duplicate)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    
    int bounds[4];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // update the boundaries
            // bounds = [left,   right, upper, lower]
            bounds[0] = (int) fmax(0, i - 1); 
            bounds[1] = (int) fmin(height - 1, i + 1);
            bounds[2] = (int) fmax(0, j - 1);
            bounds[3] = (int) fmin(width - 1, j + 1);
            
            // calculate the avg
            double cumsum[3] = {0, 0, 0};
            int cntr = 0;
            
            for (int bu = bounds[0], bd = bounds[1] + 1; bu < bd; bu++)
            {
                for (int bl = bounds[2], br = bounds[3] + 1; bl < br; bl++)
                {
                    cumsum[0]  += (double) image[bu][bl].rgbtRed;
                    cumsum[1]  += (double) image[bu][bl].rgbtGreen;
                    cumsum[2]  += (double) image[bu][bl].rgbtBlue;
                    cntr  += 1;
                }
            }
            
            // update new image's pixel
            duplicate[i][j].rgbtRed = round(cumsum[0] / cntr);
            duplicate[i][j].rgbtGreen = round(cumsum[1] / cntr);
            duplicate[i][j].rgbtBlue = round(cumsum[2] / cntr);
        }
    } 

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = duplicate[i][j].rgbtRed;
            image[i][j].rgbtGreen = duplicate[i][j].rgbtGreen;
            image[i][j].rgbtBlue = duplicate[i][j].rgbtBlue;
        }
    }
    
    free(duplicate);
    return;
}
