//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "image.h"
#include "rotate.h"

void rotate_img(img *v)
{
	// This saves the rotated image
	img f;
	double x;
	alloc_img(&f, v->sx2 - v->sx1, v->sy2 - v->sy1, v->ncolor, v->nmax,
			  v->type);
	// After the transposed one is made, the elements are switched by column
	for (int k = 0; k < f.ncolor; ++k) {
		for (int i = v->sy1; i < v->sy2; ++i)
			for (int j = v->sx1; j < v->sx2; ++j)
				f.m[k][j - v->sx1][i - v->sy1] = v->m[k][i][j];
		for (int i = 0; i < f.row; ++i)
			for (int j = 0; j < f.col / 2; ++j) {
				x = f.m[k][i][j];
				f.m[k][i][j] = f.m[k][i][f.col - j - 1];
				f.m[k][i][f.col - j - 1] = x;
		}
	}
	// The elements are put back in the original matrix
	if (v->sy2 - v->sy1 == v->sx2 - v->sx1) {
		for (int k = 0; k < f.ncolor; ++k)
			for (int i = v->sy1; i < v->sy2; ++i)
				for (int j = v->sx1; j < v->sx2; ++j)
					v->m[k][i][j] = f.m[k][i - v->sy1][j - v->sx1];
	} else {
		img temp = f;
		f = *v;
		*v = temp;
	}
	free_img(f);
}

void if_rotate(img *v, char *c)
{
	// If there is no image loaded, a specific message is shown
	if (v->type == 0) {
		printf("No image loaded\n");
		return;
	}
	// If the selection is not between the corners, then they can't be used
	if (!(v->sy2 - v->sy1 == v->sx2 - v->sx1 ||
		  (v->sy1 == 0 && v->sx1 == 0 && v->sy2 ==
		   v->row && v->sx2 == v->col))) {
		printf("The selection must be square\n");
		return;
	}
	// This verifies if the angle is below 0 or above it
	int n = 0, i = 0, minus = 0, ok = 0;
	if (c[i] == '-') {
		minus = 1;
		++i;
	}
	// Now it verifies if it is a compatible angle. If not, a message will show
	while (c[i])
		n = n * 10 + (c[i++] - '0');
	if ((minus == 0 && n == 90) || (minus == 1 && n == 270)) {
		rotate_img(v);
	} else if (n == 180) {
		rotate_img(v);
		rotate_img(v);
	} else if ((minus == 0 && n == 270) || (minus == 1 && n == 90)) {
		rotate_img(v);
		rotate_img(v);
		rotate_img(v);
	} else if (n == 360 || n == 0) {
		ok = 0;
	} else {
		printf("Unsupported rotation angle\n");
		ok = 1;
	}

	if (ok == 0) {
		if (minus == 1)
			printf("Rotated -%d\n", n);
		else
			printf("Rotated %d\n", n);
	}
}
