/* Grid handling */
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

/* Sobel Algorithm X and Y */
int sobelX[3][3] =
{
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
int sobelY[3][3] =
{
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
};

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int avg = round((
                                (double) image[i][j].rgbtBlue +
                                (double) image[i][j].rgbtGreen +
                                (double) image[i][j].rgbtRed) / 3);

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
    RGBTRIPLE(*og)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            og[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            rgbt_sum[0] = 0;
            rgbt_sum[1] = 0;
            rgbt_sum[2] = 0;

            /* Find pixel position in the image, provide x and y coordinates
             * represented in the grid, and increment divisor by affected pixels */
            int pix_pos = check_boundary(&height, &width, &i, &j);
            int x = pix_pos % 3;
            int y = pix_pos / 3;
            int i_div = 0;

            for (int k = 0; k < 3; ++k)
            {
                /* When pix_pos is represented by a coord different than zero,
                 * if k or l is equal to it, skip row or column, because it
                 * represents the edge that shouldn't be added to the average */
                if (k == y && grid3[y][x][1] != 0)
                {
                    continue;
                }

                for (int l = 0; l < 3; ++l)
                {
                    if (l == x && grid3[y][x][0] != 0)
                    {
                        continue;
                    }

                    /* Sum of all surrouding pixels per individual color */
                    rgbt_sum[0] += og[i + grid3[k][l][1]][j + grid3[k][l][0]].rgbtBlue;
                    rgbt_sum[1] += og[i + grid3[k][l][1]][j + grid3[k][l][0]].rgbtGreen;
                    rgbt_sum[2] += og[i + grid3[k][l][1]][j + grid3[k][l][0]].rgbtRed;

                    ++i_div;
                }
            }

            /* Average of surrounding pixels */
            image[i][j].rgbtBlue  = round((double) rgbt_sum[0] / i_div);
            image[i][j].rgbtGreen = round((double) rgbt_sum[1] / i_div);
            image[i][j].rgbtRed   = round((double) rgbt_sum[2] / i_div);
        }
    }

    free(rgbt_sum);
    free(og);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    /* create one set of RGB for gX, and one set of RGB for gY */
    int(*rgbt_sum)[3] = calloc(2, 3 * sizeof(int));
    RGBTRIPLE(*og)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            og[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            /* zeroing array, could possibly use with <string.h>
             * memset(rgbt_sum, 0, (2 * 3) * (sizeof *rgbt_sum)); */
            for (int l = 0; l < 3; ++l)
            {
                rgbt_sum[0][l] = 0;
                rgbt_sum[1][l] = 0;
            }

            /* check for boundaries around grid */
            for (int y = -1; y < 2; ++y)
            {
                for (int x = -1; x < 2; ++x)
                {
                    if ((i + y) < height && (i + y) > -1 && (j + x) < width && (j + x) > -1)
                    {
                        /* Calculating the magnitued of the gradient of Gx and Gy */
                        rgbt_sum[0][0] += og[i + y][j + x].rgbtBlue  * sobelX[y + 1][x + 1];
                        rgbt_sum[0][1] += og[i + y][j + x].rgbtGreen * sobelX[y + 1][x + 1];
                        rgbt_sum[0][2] += og[i + y][j + x].rgbtRed   * sobelX[y + 1][x + 1];

                        /* add gY */
                        rgbt_sum[1][0] += og[i + y][j + x].rgbtBlue  * sobelY[y + 1][x + 1];
                        rgbt_sum[1][1] += og[i + y][j + x].rgbtGreen * sobelY[y + 1][x + 1];
                        rgbt_sum[1][2] += og[i + y][j + x].rgbtRed   * sobelY[y + 1][x + 1];
                    }
                }
            }

            image[i][j].rgbtBlue  = fmin(255, round(hypot(rgbt_sum[0][0], rgbt_sum[1][0])));
            image[i][j].rgbtGreen = fmin(255, round(hypot(rgbt_sum[0][1], rgbt_sum[1][1])));
            image[i][j].rgbtRed   = fmin(255, round(hypot(rgbt_sum[0][2], rgbt_sum[1][2])));

            /*
            image[i][j].rgbtBlue = round(
                (pow(rgbt_sum[0][0], 2) + pow(rgbt_sum[1][0], 2)) / i_div);

            image[i][j].rgbtBlue = round(
                sqrt(pow(rgbt_sum[0][0], 2) + pow(rgbt_sum[1][0], 2)));
            image[i][j].rgbtGreen = round(
                sqrt(pow(rgbt_sum[0][1], 2) + pow(rgbt_sum[1][1], 2)));
            image[i][j].rgbtRed = round(
                sqrt(pow(rgbt_sum[0][2], 2) + pow(rgbt_sum[1][2], 2)));
            */
        }
    }

    free(rgbt_sum);
    free(og);
    return;
}

/* UTIL */

/* Determine position of pixel in the image */
int check_boundary(int *h, int *w, int *y, int *x)
{
    int val;

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

