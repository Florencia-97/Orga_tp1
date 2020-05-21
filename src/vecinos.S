#include <sys/regdef.h>

# ERRORES EN LINEAS 79, 104, 151, 164
# vecinos.S:161: Error: junk at end of line, first unrecognized character is `0'

# Non-leaf function.

# Argument building area (ABA).
#define ARG0 0
#define ARG1 ARG0 + 4
#define ARG2 ARG1 + 4
#define ARG3 ARG2 + 4
#define PADDING_ABA0 ARG3 + 4

# Local and Temporary Area (LTA).
#define contador PADDING_ABA0 + 4
#define c1 contador + 4
#define c2 c1 + 4
#define f  c2 + 4
#define c  f + 4
#define PADDING_LTA_0 c + 4

# Saved-registers area (SRA).
#define GP PADDING_LTA_0 + 4
#define FP GP + 4
#define RA FP + 4
#define PADDING_SRA0 RA + 4

# Caller ABA.
#define a PADDING_SRA0 + 4
#define i a + 4
#define j i + 4
#define M j + 4
#define N M + 4

#define STACK_SIZE PADDING_SRA0 + 4

.text
.align	2
.globl	vecinos
.ent	vecinos
# Debugger metadata.
.frame  fp,STACK_SIZE,ra
.set	noreorder
.cpload	t9
.set	reorder
.cprestore GP

vecinos:
    # Allocate memory for the stack.
    subu    sp,sp,STACK_SIZE
    # Save the callee-saved registers used by the caller in the SRA.
    sw      ra, RA(sp)
    sw	    fp, FP(sp)
    sw      gp, GP(sp)
    # We adopt the convention of using the frame pointer
    # as our index in the stack.
    move    fp,sp
    # Now we save the arguments that were loaded by the caller
    # in the area reserved by the callee.
    # In this case, the caller is passing us 5 arguments. 
    # Four of them through a_i registers. The last one through 
    # its ABA (counting 16B onwards, from its stack frame base).
    sw      a0, a(fp)
    sw      a1, i(fp)
    sw      a2, j(fp)
    sw      a3, M(fp)
    # ------------------------------
    ##############################
    # body: vecinos()            #
    ##############################
    sw		zero, contador(fp)

    # c1 = -1
    li		t0, -1
    sw		t0, c1(fp)
    # c1 <= 1
outer_for:
    li      t1, 1
    lw      t0, c1(fp)
    ble	    t0, t1, outer_for_body
#   j       exit_function

outer_for_body:
    # mod(i + c1, N)
    lw		t0, i(fp)
    lw		t1, c1(fp)
    addu    a0, t1, t0
    lw		a1, N(fp)
    jal		mod
    sw		v0, f(fp)

    # c2 = -1
    li		t0, -1
    sw		t0, c2(fp)
    # c2 <= 1
inner_for:
    li      t0, 1
    lw      t1, c2(fp)
    ble		t1, t0, inner_for_body

    # ++c1
    lw      t0, c1(fp)
    li      t1, 1
    addu    t0, t1, t0
    sw		t0, c1(fp)
#    j       outer_for

inner_for_body:
    # c1 == 0
    lw      t0, c1(fp)
    seq     t1, t0, zero
    # c2 == 0
    lw		t2, c2(fp)
    seq     t3, t2, zero
    # c1 && c2
    and     t0, t3, t1
    beqz    t0, inner_loop_body_continue

    # mod(j + c2, M)
    lw		t0, j(fp)
    lw		t1, c2(fp)
    addu    a0, t1, t0
    lw		a1, M(fp)
    jal		mod
    sw		v0, c(fp)

    # (a[f * M + c] == 1)
    lw		t0, f(fp)
    lw		t1, M(fp)
    lw		t2, c(fp)
    mul     t3, t0, t1
    addu    t4, t3, t2
    # access a[].
    sll     t0, t4, 2 # index.
    lw      t1, a(fp) # base.
    addu    t0, t1, t0
    lw		t0, 0(t0) # access array.
    li      t1, 1
    seq     t2, t0, t1
    beqz    t2, inner_loop_body_continue
    # contador ++
    lw      t0, contador(fp)
    li      t1, 1
    addu    t0, t0, t1
    sw      t0, contador(fp)

inner_loop_body_continue:
    # ++c2
    lw      t0, c2(fp)
    li      t1, 1
    addu    t0, t1, t0
    sw		t0, c2(fp)
#   j       inner_for

    # ------------------------------
exit_function:
    lw		v0, contador(fp)
    # Stack frame unwinding.
    lw      ra, RA(sp)
    lw      fp, FP(sp)
    lw      gp, GP(sp)
    addu    sp, sp, STACK_SIZE
#   j       ra

.end	vecinos
