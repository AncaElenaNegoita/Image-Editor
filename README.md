//Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

Image Editor

This program works as an editing app, doing the basic instructions that are
needed in order to modify the photo in various ways. It can be easily
ajusted and used in real life, in an app. I may say its photoshop itself. :)

There are a lot of functions that work in this program:

- LOAD <fisier> -the image is uploaded and the space is allocated in memory.
If a photo is already there, it will be freed and the new one will take its 
place.

- SELECT <x1 x2 x3 x4> -a specific section from the photo is saved in 4 
different variables in struct. If any coordinate is not right, "Invalid 
coordinates" will appear. Also, in this function, swappes are made
in order to have the coordinates in order. (x1 < x2 && y1 < y2)

- SELECT ALL -all the corners from the photo are selected and saved in
4 different variables in struct

- ROTATE <unghi> -the whole image is rotated in a specific direction to
a specific angle. If the angles are positive, they rotate clockwise, else,
the other way. If an angle is not compatible, "Unsupported rotation angle"
will appear. Also the function verifies if the whole photo is selected or
a square. Else, the rotation doesn't work

- CROP -a specific section will become the new photo. The function uses
the 4 variables mentioned earlier and the section will replace the old
photo.

- APPLY <parametru> -a filter is applied to the selection. The same formula is
applied no matter what the parameter is, the only difference is the matrix
named kernel that helps calculate. If there is an invalid filter, "APPLY 
parameter invalid" will show. Also, if the photo is black and white, a funny
message will appear, which is "Easy, Charlie Chaplin"

- SAVE <name> ascii(or not) -the prelucrated photo will be saved in a folder
with a specific name. The function verifies if after the name there is the
word "ascii" written. If it is, the photo is saved ascii, else, binary.

- EXIT -the program closes and the memory is freed

Also, for each task, if there aren't any images loaded, "No image loaded"
will appear and nothing will happen.
