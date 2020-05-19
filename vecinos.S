.data
ime: .asciiz "TP1 Game of Life"

# argumento 'a5' - 24

# a3 - 20
# a2 - 16
# a1 - 12
# a0 - 8

# Stack
# fp - 4
# gp - 0

.text
.align 2
.globl vecinos
.ent vecinos
.set noreorder
.cpload t9
.set reorder

vecinos:
	# creo stack
	subu sp, sp, 8
	.cprestore 0
	sw fp, 4(sp)
	sw gp, 0(sp)
    move fp,sp
    # cargo los argumentos
    sw	a0,8(fp)	# a puntero a prmera pos del arreglo
    sw	a1,12(fp)	# i fila
    sw	a2,16(fp)	# j columna
    sw	a3,20(fp)	# M length
    lw $t0,24(sp)   # N height

    li v0, 0 # v0 es el valor a devolver y por ende contador
    li $t1, -1 # c1
    li $t2, -1 # c2
    li $t3, 2 # Para cortar el loop

LOOP_FILAS: 
    beq $t1, $t3, BREAK # Si c1 vale 2 corto loop
    # implementar modulo, asumo f en t4 por ahora
LOOP_COLS:    
    beq $t2, $t3, LOOP_FILAS # Si c2 vuelvo a loop_filas
    # implementar modulo, asumo c en t5 por ahora
    # ver como ignorar la posición q estoy mirando, para
    # no contarla como vecino
    li $t6, 0
    add $t6, $t6, $t5 # sumo c
    li $t7, 0
    mul $t7,$t7, a3 # hago f*m
    # Ahora deberia tener en t6 la dir a la que avanzar
    addu $t6, $t6, a0
    # Ahora deberia tener en t6 el valor en la pos pedida
    ld $t6, $t6
    # Chequeo si es 1
    li $t8,1
    bneq $t6, $t8, LOOP_COLS
    addu v0, v0, 1
    j LOOP_FILAS


BREAK:
    # implementar end, debe retornar v0
    move    sp,fp
    lw    fp,4(sp)
    addiu    sp,sp,8

.end vecinos