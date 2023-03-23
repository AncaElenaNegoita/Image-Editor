//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "image.h"

// This functions is used to load a new image
void load_matrix(img * v, char *p);

// This functions is used to save an image
void save_img(img v, char *name, int ascii);
