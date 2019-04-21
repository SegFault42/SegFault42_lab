.globl _start
.section .text

_start:

	mov w0, #1
	adrp x1, message
	mov w2, #6
	svc #0


	mov x8, #93
	mov x0, #42
	svc #0

	ret

.section .rodata
message:
	.asciz	"Hello world!\n"

