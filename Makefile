# Copyright (C) 2022 Negoita Anca-Elena (311CA / 2021-2022)

build: image_editor 

image_editor:
	gcc -Wall -Wextra *.c -lm -o image_editor

pack:
	zip -FSr 311CA_Negoita_Anca_Elena_Tema3.zip README Makefile *.c *.h

clean:
	rm image_editor

.PHONY: pack clean
