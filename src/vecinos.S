#include <sys/regdef.h>

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

.set	noreorder
.cpload	t9
.set	reorder

vecinos:
    # Allocate memory for the stack.
    subu	sp,sp,STACK_SIZE
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
    # Four of them through 'a' registers. The last one through 
    # its ABA (counting 16B onwards, from its stack frame base).
    sw      a0, a(fp)
    sw      a1, i(fp)
    sw      a2, j(fp)
    sw      a3, M(fp)
    # ------------------------------
    ##############################
    # body: vecinos()            #
    ##############################








    # ------------------------------
exit_function:
    # Stack frame unwinding.
    lw      ra, RA(sp)
    lw      fp, FP(sp)
    lw      gp, GP(sp)
    addu    sp, sp, STACK_SIZE
    j       ra

.end	vecinos