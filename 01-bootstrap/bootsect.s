    # Skelix by Xiaoming Mo (skelixos@gmail.com)
    # Licence: GPLv2

	.text
	.globl	start
	.code16

start:
	jmpl	$0x0,	$code

msg:
	.string	"Hello World!\x0"

code:
    mov     $0x06,  %ah
    mov     $0,     %al
    mov     $0,     %cx
    mov     $0xffff,%dx
    mov     $0x17,  %bh
    int     $0x10

    movw	$0xb800,%ax
	movw	%ax,	%es
	xorw	%ax,	%ax
	movw	%ax,	%ds

	movw	$msg,	%si
	xorw	%di,	%di
	
	cld
	movb	$0x1f,	%al
1:
	cmpw	$0,	(%si)
	je	1f	
	movsb
	stosb
	jmp	1b
1:
    jmp	1b

    .org	0x1fe, 0x90
    .word	0xaa55
