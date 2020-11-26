#include <stdlib.h>
#include <math.h>

#include "helpers.h"

/* Grid 3x3 XY position of individual cells */
int grid3[3][3][2] =
{
    {{-1, -1}, {0, -1}, {1, -1}}, /* 0, 1, 2 */
    {{-1, 0},  {0, 0},  {1, 0}},  /* 3, 4, 5 */
    {{-1, 1},  {0, 1},  {1, 1}}   /* 6, 7, 8 */
};

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            BYTE avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue  = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed   = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *temp = malloc(sizeof(RGBTRIPLE));
    int half_w = (int) floor(width / 2);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < half_w; ++j)
        {
            *temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = *temp;
        }
    }

    free(temp);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int *rgbt_sum = malloc(3 * sizeof(int));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            rgbt_sum[0] = 0;
            rgbt_sum[1] = 0;
            rgbt_sum[2] = 0;

            /* Find pixel position in the image, provide x and y coordinates
             * represented in the grid, and increase divisor by affect pixels */
            int pix_pos = check_boundary(&height, &width, &i, &j);
            int x = pix_pos % 3;
            int y = pix_pos / 3;
            int i_div = 0;

            for (int k = 0; k < 3; ++k)
            {
                /* When pix_pos is represented by a coord different than zero,
                 * if k or l is equal to it, skip row or column, because it
                 * represents the edge that shouldn't be added to the average */
                if (grid3[y][x][1] != 0 && k == y)
                {
                    continue;
                }

                for (int l = 0; l < 3; ++l)
                {
                    if (grid3[y][x][0] != 0 && l == x)
                    {
                        continue;
                    }

                    /* Sum of all surrouding pixels per individual color */
                    rgbt_sum[0] += image[i+grid3[k][l][1]][j+grid3[k][l][0]].rgbtBlue;
                    rgbt_sum[1] += image[i+grid3[k][l][1]][j+grid3[k][l][0]].rgbtGreen;
                    rgbt_sum[2] += image[i+grid3[k][l][1]][j+grid3[k][l][0]].rgbtRed;

                    ++i_div;
                }
            }

            /* Average of surrounding pixels */
            image[i][j].rgbtBlue  = round(rgbt_sum[0] / i_div);
            image[i][j].rgbtGreen = round(rgbt_sum[1] / i_div);
            image[i][j].rgbtRed   = round(rgbt_sum[2] / i_div);
        }
    }

    free(rgbt_sum);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

/* UTIL */

/* Determine position of pixel in the image */
int check_boundary(int *h, int *w, int *y, int *x)
{
    int val;

    if ()

    if (*y < 1)
    {
        if (*x < 1)
        {
            val = 0;
        }
        else if (*x >= *w - 1)
        {
            val = 2;
        }
        else
        {
            val = 1;
        }
    }
    else if (*y >= *h - 1)
    {
        if (*x < 1)
        {
            val = 6;
        }
        else if (*x >= *w - 1)
        {
            val = 8;
        }
        else
        {
            val = 7;
        }
    }
    else if (*x < 1)
    {
        val = 3;
    }
    else if (*x >= *w - 1)
    {
        val = 5;
    }
    else
    {
        val = 4;
    }

    return val;
}

