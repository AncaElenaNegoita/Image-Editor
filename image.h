//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
	int row, col, nmax, ncolor, type;
	double ***m;
	int sx1, sx2, sy1, sy2;
} img;

// This function allocates space in memory for the matrices that will be used
void alloc_img(img *v, int row, int col, int color, int nmax, int type);

//This functtion frees the space we previously allocated
void free_img(img f);
