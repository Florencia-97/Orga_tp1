all:
	gcc -Wall -g -o conway *.c vecinos.S

mips:
	gcc -Wall -mips32  -g -o conway *.c vecinos.S