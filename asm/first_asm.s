.section .text
.global main

main:
	movl $1, %eax
	movl $20, %ebx
	int $0x80
