//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "image.h"

void alloc_img(img *v, int row, int col, int color, int nmax, int type)
{
	v->row = row;
	v->col = col;
	v->ncolor = color;
	v->nmax = nmax;
	v->type = type;
	// This allocates space for the array of matrices
	v->m = malloc(v->ncolor * sizeof(double **));
	for (int i = 0; i < v->ncolor; ++i) {
		// This allocates space for the rows of a matrix
		v->m[i] = malloc(v->row * sizeof(double *));
		for (int j = 0; j < v->row; ++j)
			v->m[i][j] = malloc(v->col * sizeof(double));
	}
	v->sx1 = 0;
	v->sx2 = col;
	v->sy1 = 0;
	v->sy2 = row;
}

void free_img(img f)
{
	for (int i = 0; i < f.ncolor; ++i) {
		for (int j = 0; j < f.row; ++j)
			free(f.m[i][j]);
		free(f.m[i]);
	}
	free(f.m);
	// The difference between allocate and free is that free works backwards.
	// First, each row is freed, then each matrix, and in the end the array of
	//matrices
}
