#include <sys/regdef.h>

# Leaf function.

# Local and Temporary Area (LTA).
#define r 0
#define PADDING_LTA_0 r + 4

# Saved-registers area (SRA).
#define GP PADDING_LTA_0 + 4
#define FP GP + 4

# Caller ABA.
#define x FP + 4
#define m x + 4

#define STACK_SIZE FP + 4

.text
.align	2
.globl	mod
.ent	mod

.set	noreorder
.cpload	t9
.set	reorder

mod:
    # Allocate memory for the stack.
    subu	sp,sp,STACK_SIZE
    # Save the callee-saved registers used by the caller in the SRA.
    sw	    fp,FP(sp)
.cprestore GP # Equivalent to     sw      gp, GP(sp).
    # We adopt the convention of using the frame pointer
    # as our index in the stack.
    move    fp,sp
    # Now we save the arguments that were loaded by the caller
    # in the area reserved by the callee.
    sw      a0, x(fp)
    sw      a1, m(fp)
    # ------------------------------
    ##############################
    # body: mod()                #
    ##############################
    remu    t0,a0,a1
    sw      t0,r(fp)
    blt     t0, zero, r_plus_m
    lw		v0, r(fp)
    b		exit_function

r_plus_m:
    add		v0, t0, a1
    # ------------------------------
exit_function:
    # Stack frame unwinding.
    lw      fp, FP(sp)
    lw      gp, GP(sp)
    addu    sp, sp, STACK_SIZE
    jr      ra

.end	mod