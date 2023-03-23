//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "select.h"
#include "image.h"

int string_to_number(char *p, int *ok, int *minus)
{
	// This verifies if the parameters exit
	if (!p) {
		printf("Invalid command\n");
		*ok = 0;
		return 0;
	}
	// This verifies if the parameter is below 0(negative)
	int i = 0, x = 0;
	if (p[i] == '-') {
		*minus = 1;
		++i;
	}
	// This verifies if the parameter is a number
	while (p[i]) {
		if (p[i] < '0' || p[i] > '9') {
			printf("Invalid command\n");
			*ok = 0;
			return 0;
		}
		x = x * 10 + (p[i++] - '0');
	}

	return x;
}

void select_all(img *v)
{
	// If there is no image loaded, a specific message is shown
	if (v->type == 0) {
		printf("No image loaded\n");
		return;
	}
	// This select all corners of the photo and saves them in variables
	v->sx1 = 0;
	v->sx2 = v->col;
	v->sy1 = 0;
	v->sy2 = v->row;
	printf("Selected ALL\n");
}

void select_(img *v, int n[4], int nr)
{
	// If there is no image loaded, a specific message is shown
	if (v->type == 0) {
		printf("No image loaded\n");
		return;
	}
	if (nr == 0) {
		printf("Invalid command\n");
		return;
	}
	// If the coordonates are swapped, they are put in the right place
	if (n[0] > n[2]) {
		int x = n[0];
		n[0] = n[2];
		n[2] = x;
	}
	if (n[1] > n[3]) {
		int x = n[1];
		n[1] = n[3];
		n[3] = x;
	}
	// If they don't respect all the criterias, it shows a message
	if (n[0] == n[2] || n[1] == n[3] || n[0] < 0 || n[1] < 0 ||
		n[2] > v->col || n[3] > v->row) {
		printf("Invalid set of coordinates\n");
		return;
	}

	v->sx1 = n[0];
	v->sy1 = n[1];
	v->sx2 = n[2];
	v->sy2 = n[3];

	printf("Selected %d %d %d %d\n", v->sx1, v->sy1, v->sx2, v->sy2);
}
