//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "image.h"

// This function rotates the image at a specific angle
void rotate_img(img * v);

// This function verifies if it is a correct angle and calls the one above
void if_rotate(img *v, char *c);
