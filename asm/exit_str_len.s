.section .data
string:
	.asciz "EREWREW1!\n"

.section .text
.global main

main:
	movq $string, %rsi
	movb $0, %cl

loop:
	movb (%rsi), %al
	testb %al, %al
	jz end

	incq %rsi
	inc %cl
	jmp loop

end:
	movq $60, %rax
	movzx %cl, %rdi
	syscall
