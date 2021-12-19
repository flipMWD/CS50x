#include <stdlib.h>
#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
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

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < half_w; ++j) {
			*temp = image[i][j];
			image[i][j] = image[i][width-1-j];
			image[i][width-1-j] = *temp;
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

	// Copy original image to used when reading the grid
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			og[i][j] = image[i][j];
		}
	}

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int i_div = 0;

			rgbt_sum[0] = 0;
			rgbt_sum[1] = 0;
			rgbt_sum[2] = 0;

			// Check sourrounding pixels on a 3x3 grid
			for (int y = -1; y < 2; ++y) {
				for (int x = -1; x < 2; ++x) {
					if ((y + i) < height && (y + i) > -1 &&
						(x + j) < width  && (x + j) > -1) {
						rgbt_sum[0] += og[y+i][x+j].rgbtBlue;
						rgbt_sum[1] += og[y+i][x+j].rgbtGree;
						rgbt_sum[2] += og[y+i][x+j].rgbtRed;

						++i_div;
					}
				}
			}

			// Average of surrounding pixels
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
	// Temporary array for Gx RGB and Gy RGB colors
	int(*rgbt_sum)[3] = calloc(2, 3 * sizeof(int));

	// Keep image source to check surrounding pixels
	RGBTRIPLE(*og)[width] = calloc(height, width * sizeof(RGBTRIPLE));

	// Sobel algorithm: G = √(Gx² + Gy²)
	int sobelX[3][3] = {
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1}
	};

	int sobelY[3][3] = {
		{-1, -2, -1},
		{0, 0, 0},
		{1, 2, 1}
	};


	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			og[i][j] = image[i][j];
		}
	}

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			// <string.h> memset(rgbt_sum, 0, (2 * 3) * (sizeof *rgbt_sum));
			for (int l = 0; l < 3; ++l) {
				rgbt_sum[0][l] = 0;
				rgbt_sum[1][l] = 0;
			}

			// Check surrounding pixels and apply Sobel Operator
			for (int y = -1; y < 2; ++y) {
				for (int x = -1; x < 2; ++x) {
					if ((i + y) < height && (i + y) > -1 &&
						(j + x) < width  && (j + x) > -1) {
						// Calculate the magnitued of the gradient for Gx and Gy
						rgbt_sum[0][0] += og[i+y][j+x].rgbtBlue *
							sobelX[y+1][x+1];
						rgbt_sum[0][1] += og[i+y][j+x].rgbtGreen *
							sobelX[y+1][x+1];
						rgbt_sum[0][2] += og[i+y][j+x].rgbtRed *
							sobelX[y+1][x+1];

						rgbt_sum[1][0] += og[i+y][j+x].rgbtBlue *
							sobelY[y+1][x+1];
						rgbt_sum[1][1] += og[i+y][j+x].rgbtGreen *
							sobelY[y+1][x+1];
						rgbt_sum[1][2] += og[i+y][j+x].rgbtRed *
							sobelY[y+1][x+1];
					}
				}
			}

			image[i][j].rgbtBlue  = fmin(255, round(
				hypot(rgbt_sum[0][0], rgbt_sum[1][0])));
			image[i][j].rgbtGreen = fmin(255, round(
				hypot(rgbt_sum[0][1], rgbt_sum[1][1])));
			image[i][j].rgbtRed   = fmin(255, round(
				hypot(rgbt_sum[0][2], rgbt_sum[1][2])));
		}
	}

	free(rgbt_sum);
	free(og);
	return;
}
