.section .data
string:
	.asciz "Hello World!\n"
string_len:
	.long . - string - 1

.section .text
.global main

main:
	movq $1, %rax
	movq $1, %rdi
	movq $string, %rsi
	movq string_len, %rdx
	syscall

	movq $60, %rax
	movq $20, %rdi
	syscall
