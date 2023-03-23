//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "image.h"

// This function converts the text into numbers
int string_to_number(char *p, int *ok, int *minus);

// This function saves the coordinates of the whole photo
void select_all(img *v);

// This function saves the coorf=dinates of a specific section
void select_(img *v, int n[4], int nr);
