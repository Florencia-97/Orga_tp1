# ------------------------------------------------------------
#
# The source files must have .c extension.
# The object code must have .o extension.
# The header files must have .h extension.
#
# To compile, execute 'make'.
# To clean all the compilation files, issue the command
# 'make clean'.
#
# ------------------------------------------------------------
# List all the header and object files separated by a blank
# space.
_DEPS = params_t.h messages.h
_SRC1_c = conway.c tablero.c cmd_line_parser.c vecinos.c mod.c
_SRC1_S = conway.c tablero.c cmd_line_parser.c vecinos.S mod.S
# ------------------------------------------------------------
# Configuration.
CC = gcc
CFLAGS = -Wall -O0 -g -mips32 -mlong32
OUTPUT1 = conway
# ------------------------------------------------------------
all: $(OUTPUT1)

$(OUTPUT1): $(_SRC1_c) 
	$(CC) $(CFLAGS) -o $@ $(_SRC1_c)

use_S_files: $(_SRC1_s) 
	$(CC) $(CFLAGS) -o $(OUTPUT1) $(_SRC1_S)

.PHONY: clean use_S_files

clean:
	rm -f ./*.o ./*~ ./*.core ./*~
	rm -f $(OUTPUT1)
