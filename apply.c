// //Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "image.h"
#include "apply.h"

double clamp(double x, int min, int max)
{
	if (x < min)
		return min;
	if (x > max)
		return max;
	return x;
}

void apply_effect_on_image(img *v, const double kernel[][3])
{
	// This matrix saves the last matrix, but with the applied filter
	img temp;
	alloc_img(&temp, v->sy2 - v->sy1, v->sx2 - v->sx1, v->ncolor, v->nmax,
			  v->type);
	// If the point has neighbours, then the formula is applied in temp
	for (int k = 0; k < v->ncolor; ++k)
		for (int i = v->sy1; i < v->sy2; ++i)
			for (int j = v->sx1; j < v->sx2; ++j)
				if (i != 0 && j != 0 && i != v->row - 1 && j != v->col - 1) {
					double x = kernel[0][0]		*	v->m[k][i - 1][j - 1]	+
							   kernel[0][1]		*	v->m[k][i - 1][j]		+
							   kernel[0][2]		*	v->m[k][i - 1][j + 1]	+
							   kernel[1][0]		*	v->m[k][i][j - 1]		+
							   kernel[1][1]		*	v->m[k][i][j]			+
							   kernel[1][2]		*	v->m[k][i][j + 1]		+
							   kernel[2][0]		*	v->m[k][i + 1][j - 1]	+
							   kernel[2][1]		*	v->m[k][i + 1][j]		+
							   kernel[2][2]		*	v->m[k][i + 1][j + 1];
					temp.m[k][i - v->sy1][j - v->sx1] =
					clamp(x, 0, temp.nmax);
				} else {
					temp.m[k][i - v->sy1][j - v->sx1] = v->m[k][i][j];
				}
	// The elements from temp are transfered to the initial matrix
	for (int k = 0; k < v->ncolor; ++k)
		for (int i = v->sy1; i < v->sy2; ++i)
			for (int j = v->sx1; j < v->sx2; ++j)
				v->m[k][i][j] = temp.m[k][i - v->sy1][j - v->sx1];
	free_img(temp);
}

void apply_effect(img *v, char *p)
{
	// If there is no image loaded, a specific message is shown
	if (v->type == 0) {
		printf("No image loaded\n");
		return;
	}
	const double kernel_edge[3][3] = {{-1, -1, -1},
									  {-1,  8, -1},
									  {-1, -1, -1}};
	const double kernel_sharpen[3][3] = {{0, -1, 0},
										 {-1, 5, -1},
										 {0, -1, 0}};
	const double kernel_blur[3][3] = {{0.111, 0.111, 0.111},
									  {0.111, 0.111, 0.111},
									  {0.111, 0.111, 0.111}};
	const double kernel_gaussian_blur[3][3] = {{0.0625, 0.125, 0.0625},
											   {0.125, 0.25, 0.125},
											   {0.0625, 0.125, 0.0625}};
	// If the effect doesn't exist, then on the screen will appear this message
	if (!p) {
		printf("Invalid command\n");
		return;
	}
	// If the photo is black and white, a specific message is shown
	if (v->type == 2) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}
	// This verifies which effect is used
	if (strcmp(p, "EDGE") == 0) {
		apply_effect_on_image(v, kernel_edge);
	} else if (strcmp(p, "SHARPEN") == 0) {
		apply_effect_on_image(v, kernel_sharpen);
	} else if (strcmp(p, "BLUR") == 0) {
		apply_effect_on_image(v, kernel_blur);
	} else if (strcmp(p, "GAUSSIAN_BLUR") == 0) {
		apply_effect_on_image(v, kernel_gaussian_blur);
	} else {
		printf("APPLY parameter invalid\n");
		return;
	}

	printf("APPLY %s done\n", p);
}
