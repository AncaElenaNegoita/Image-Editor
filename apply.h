//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "image.h"

// This function verifies if the number is either bigger than the maximum
//or lower
double clamp(double x, int min, int max);

// This function applies the formula to obtain the effect
void apply_effect_on_image(img *v, const double kernel[][3]);

// This function calls the one above to calculate a specific effect
void apply_effect(img *v, char *p);
