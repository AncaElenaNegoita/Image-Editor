//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "crop.h"
#include "image.h"

void crop_img(img *v)
{
	// If there is no image loaded, a specific message is shown
	if (v->type == 0) {
		printf("No image loaded\n");
		return;
	}
	// This copy saves the cropped photo
	img f = *v;
	alloc_img(&f, v->sy2 - v->sy1, v->sx2 - v->sx1, v->ncolor, v->nmax,
			  v->type);
	// This matrix saves the specific selection
	for (int k = 0; k < f.ncolor; ++k) {
		for (int i = 0; i < f.row; ++i)
			for (int j = 0; j < f.col; ++j)
				f.m[k][i][j] = v->m[k][v->sy1 + i][v->sx1 + j];
	}
	free_img(*v);
	*v = f;
	printf("Image cropped\n");
}
