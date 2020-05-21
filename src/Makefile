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
_DEPS = params_t.h
# If needed, use the MIPS .S file. Just replace 'vecinos.c' 
# with 'vecinos.s'.
_SRC1 = conway.c tablero.c cmd_line_parser.c vecinos.c mod.S
_OBJ1 = conway.o tablero.o cmd_line_parser.o
# ------------------------------------------------------------
# Configuration.
CC = gcc
CFLAGS = -Wall -O0 -g -mips32 -mlong32
OUTPUT1 = conway
# ------------------------------------------------------------
all: $(OUTPUT1)

$(OUTPUT1): $(_SRC1) 
	$(CC) $(CFLAGS) -o $@ $(_SRC1)

assembly:
	$(CC) $(CFLAGS) -S $(_SRC1)

.PHONY: clean assembly

clean:
	rm -f ./*.o ./*~ ./*.core ./*~
	rm -f $(OUTPUT1)
