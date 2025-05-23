.section .data

string:
	.asciz "mystring"
printf_format:
	.asciz "%s has a length of %d\n" 

.section .text
.global main
.extern printf

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
	movq $printf_format, %rdi	#1st printf arg
	movq $string, %rsi			#2nd printf arg
	movzx %cl, %rdx				#3rd printf arg

	xorq %rax, %rax				#rax register used by va_arg in printf

	addq $8, %rsp				#16-bytes alignment before calling c functions
	call printf
	addq $8, %rsp				#16-bytes alignment after calling c functions

	movq %rax, %rdi				#exit_status => printf return value
	movq $60, %rax
	syscall
