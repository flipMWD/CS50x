// Scrapped

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int *rgbt_sum = malloc(3*sizeof(int));
    int byte_s = sizeof(BYTE);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            rgbt_sum = {0, 0, 0};

            /* MAGIC */
            for (int k = 0; k < 9; ++k)
            {
                for (int l = 0; l < 3; ++l)
                {
                    rgbt_sum[l] += (int) *(image[i][j] + (l * byte_s));
                }
                /*
                rgbt_sum[0] += image[i][j].rgbtBlue; // may possibly need to cast (int)
                rgbt_sum[1] += image[i][j].rgbtGreen;
                rgbt_sum[2] += image[i][j].rgbtRed;
                */
            }

            image[i][j].rgbtBlue  = round(rgbt_sum[0] / 9); /* lit 9 could be 6 or 4 */
            image[i][j].rgbtGreen = round(rgbt_sum[1] / 9);
            image[i][j].rgbtRed   = round(rgbt_sum[2] / 9);
        }
    }

    free(rgbt_sum);
    return;
}

int get_pos(int h, int w, int y, int x)
{
    int pos;

    if (y < 1)
    {
        pos = /* find a way to arithmetically calculate [i - 1][j + 1]... above */
    }
    return pos;
}

// New Version

#include <stdlib.h>
#include <math.h>

#include "helpers.h"

/* maybe leave as global [3][3][2] instead of heap buffer
int *k_grid[KERNEL_XY] = calloc(KERNEL_3X3, sizeof(int[KERNEL_XY]));
k_grid = */
int k_grid[9][2] =
{
    {-1, -1}, {0, -1}, {1, -1}, /* 0, 1, 2 */
    {-1, 0},  {0, 0},  {1, 0},  /* 3, 4, 5 */
    {-1, 1},  {0, 1},  {1, 1}   /* 6, 7, 8 */
};

void read_kernel(int p, int x, int y, RGBTRIPLE s, int *o)
{
    int byte_s = sizeof(BYTE);
    int stct_s = sizeof(RGBTRIPLE) / byte_s;

    /* calc start, end and step based on pos.
     * consider condition block instead of iteration. */
    for (int k = 0; k < 9; ++k)
    {
        /* would only work with k_grid as a tensor */
        if (p != 4 && (k == p)) continue;

        for (int m = 0; m < stct_s; ++m)
        {
            o[m] += (int) *(s[y + k_grid[k][1]][x + k_grid[k][0]]) + (m * byte_s);
        }
    }
}

int check_boundery(int *w, int *h, int *x, int *y)
{
    /* TODO: Determine arithmetically the position
     * 100 + 0 % 100 == 0
     * 100 + 99 % 100 == 99
     *
     * 200 + 0 % 200 == 0
     * 200 + 199 % 200 = 199
     */

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

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int *rgbt_sum = malloc(3 * sizeof(int));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            rgbt_sum[0] = 0; rgbt_sum[1] = 0; rgbt_sum[2] = 0;
            int k_pos = check_boundery(&width, &height, &j, &i);
            read_kernel(k_pos, j, i, image[i][j], rgbt_sum);

            if (i < 1)
            {
                if (j < 1) /* pos 1/9 */
                {
                    rgbt_sum[0] += image[i][j].rgbtBlue; // may possibly need to cast (int)
                    rgbt_sum[1] += image[i][j].rgbtGreen;
                    rgbt_sum[2] += image[i][j].rgbtRed;
                }
                else if (j > width - 2) /* pos 3/9 */
                {
                    rgbt_sum[0] += image[i][j].rgbtBlue;
                    rgbt_sum[1] += image[i][j].rgbtGreen;
                    rgbt_sum[2] += image[i][j].rgbtRed;
                }
            }

            /* create fn to detect affected nodes and return value to variable */
            image[i][j].rgbtBlue  = round(rgbt_sum[0] / 9); /* lit 9 could be 6 or 4 */
            image[i][j].rgbtGreen = round(rgbt_sum[1] / 9);
            image[i][j].rgbtRed   = round(rgbt_sum[2] / 9);
        }
    }

    free(rgbt_sum);
    return;
}
