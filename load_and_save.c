//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "image.h"
#include "load_and_save.h"

void load_matrix(img *v, char *p)
{
	char c[100];
	// This opens the file in need
	FILE *fin = fopen(p, "rt");
	// If there is an array of matrices and another one needs to be loaded, the
	//previous one will be deleted
	if (v->type != 0)
		free_img(*v);
	v->type = 0;
	v->sx1 = 0;
	v->sy1 = 0;
	v->sx2 = 0;
	v->sy2 = 0;
	// If the photo doesn't exist, a specific message is shown
	if (!fin) {
		printf("Failed to load %s\n", p);
		return;
	}
	// This reads until no comment appears anymore
	fgets(c, 100, fin);
	while (c[0] == '#')
		fgets(c, 100, fin);
	// This verifies which type of photo is loaded
	if ((c[1] - '0') % 3 == 0) {
		v->ncolor = 3;
		v->type = 3;
	} else {
		v->ncolor = 1;
		v->type = 2;
	}

	fscanf(fin, "%d%d%d", &v->col, &v->row, &v->nmax);

	alloc_img(v, v->row, v->col, v->ncolor, v->nmax, v->type);
	// If the photo is binar, the file reopens to be read specifically
	if ((c[1] - '0') >= 5) {
		int pos = ftell(fin);
		freopen(p, "rb", fin);
		fseek(fin, pos + 1, SEEK_SET);
	}
	// The elements are loaded in their matrix
	for (int i = 0; i < v->row; ++i)
		for (int j = 0; j < v->col; ++j)
			for (int k = 0; k < v->ncolor; ++k) {
				if ((c[1] - '0') >= 5) {
					unsigned char temp;
					fread(&temp, 1, 1, fin);
					v->m[k][i][j] = temp;
				} else {
					fscanf(fin, "%lf", &v->m[k][i][j]);
				}
			}
	fclose(fin);
	printf("Loaded %s\n", p);
}

void save_img(img v, char *name, int ascii)
{
	unsigned char temp = 0;
	// If there is no image loaded, a specific message is shown
	if (v.type == 0) {
		printf("No image loaded\n");
		return;
	}

	FILE *fout;
	// The file is either saved as ascii or binar
	if (ascii == 1) {
		fout = fopen(name, "wt");
		fprintf(fout, "P%d\n", v.type);
	} else {
		fout = fopen(name, "wb");
		fprintf(fout, "P%d\n", v.type + 3);
	}
	fprintf(fout, "%d %d\n%d\n", v.col, v.row, v.nmax);
	for (int i = 0; i < v.row; ++i) {
		for (int j = 0; j < v.col; ++j)
			for (int k = 0; k < v.ncolor; ++k) {
				temp = round(v.m[k][i][j]);
				if (ascii == 0)
					fwrite(&temp, 1, 1, fout);
				else
					fprintf(fout, "%hhu ", temp);
			}
		if (ascii == 1)
			fprintf(fout, "\n");
	}
	printf("Saved %s\n", name);
	fclose(fout);
}
