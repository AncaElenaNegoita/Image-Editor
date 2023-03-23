//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "image.h"
#include "load_and_save.h"
#include "crop.h"
#include "apply.h"
#include "select.h"
#include "rotate.h"

int main(void)
{
	img v;
	v.type = 0;
	char c[100];
	char *p;
	// A whole line is read, and strtok is used to get each word we need
	fgets(c, 100, stdin);
	// Everything happens until the user writes the word "EXIT"
	while (!strstr(c, "EXIT")) {
		p = strtok(c, "\n ");
		// This is used to upload a new photo
		if (strcmp(p, "LOAD") == 0) {
			p = strtok(NULL, "\n ");
			load_matrix(&v, p);
		// This is used to select a specific area
		} else if (strcmp(p, "SELECT") == 0) {
			p = strtok(NULL, "\n ");
			// The whole photo can be selected using "SELECT ALL"
			if (strcmp(p, "ALL") == 0) {
				select_all(&v);
			//A small squared portion from the photo can be selected
			} else {
				// The program verifies if there's a photo uploaded in order to
				//select
				if (v.type == 0) {
					printf("No image loaded\n");
					fgets(c, 100, stdin);
					continue;
				}
				// The coordinates are read and converted to int
				int n[4] = {0}, nr = 0, ok = 1, minus = 0;
				while (nr < 4 && ok) {
					n[nr++] = string_to_number(p, &ok, &minus);
					p = strtok(NULL, "\n ");
				}
				// If a coordinate doesn't respect a rule, the set is invalid
				if (!minus && ok)
					select_(&v, n, nr);
				else if (minus && ok)
					printf("Invalid set of coordinates\n");
			}
		// This is used to rotate a selected area from the photo
		} else if (strcmp(p, "ROTATE") == 0) {
			p = strtok(NULL, "\n ");
			if_rotate(&v, p);
		// This is used to crop a selected area, the new photo becoming the
		//one in between the selection
		} else if (strcmp(p, "CROP") == 0) {
			crop_img(&v);
		// This is used to save the current photo
		} else if (strcmp(p, "SAVE") == 0) {
			char *name = strtok(NULL, "\n ");
			p = strtok(NULL, "\n ");
			// The program verifies if it is binary or ascii
			int ascii;
			if (p && strcmp(p, "ascii") == 0)
				ascii = 1;
			else
				ascii = 0;

			save_img(v, name, ascii);
		// This is used to apply effects on a selected area
		} else if (strcmp(p, "APPLY") == 0) {
			p = strtok(NULL, "\n ");
			apply_effect(&v, p);
		} else {
		// If there is no known command, this appears
			printf("Invalid command\n");
		}
		fgets(c, 100, stdin);
	}
	// If "EXIT" is used at the begining and no photo was uploaded, this message
	//will appear
	if (v.type == 0)
		printf("No image loaded\n");
	else
		free_img(v); // The allocated space is freed
	return 0;
}
