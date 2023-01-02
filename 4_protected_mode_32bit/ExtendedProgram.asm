[org 0x7e00]

jmp EnterProtectedMode

%include "gdt.asm"
%include "print.asm"

EnterProtectedMode:
	call EnableA20
	cli			; disable interrupts
	lgdt [gdt_descriptor]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp codeseg:StartProtectedMode

EnableA20:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret

[bits 32]

StartProtectedMode:
	mov ax, dataseg
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov [0xb8000], byte 'H'
	mov [0xb8001], byte 0x1f
	mov [0xb8002], byte 'e'
	mov [0xb8003], byte 0x1f
	mov [0xb8004], byte 'l'
	mov [0xb8005], byte 0x1f
	mov [0xb8006], byte 'l'
	mov [0xb8007], byte 0x1f
	mov [0xb8008], byte 'o'
	mov [0xb8009], byte 0x1f
	mov [0xb800a], byte ' '
	mov [0xb800b], byte 0x1f
	mov [0xb800c], byte 'w'
	mov [0xb800d], byte 0x1f
	mov [0xb800e], byte 'o'
	mov [0xb800f], byte 0x1f
	mov [0xb8010], byte 'r'
	mov [0xb8011], byte 0x1f
	mov [0xb8012], byte 'l'
	mov [0xb8013], byte 0x1f
	mov [0xb8014], byte 'd'
	mov [0xb8015], byte 0x1f
	mov [0xb8016], byte ' '
	mov [0xb8017], byte 0x1f
	mov [0xb8018], byte '^'
	mov [0xb8019], byte 0x1f
	mov [0xb801a], byte '_'
	mov [0xb801b], byte 0x1f
	mov [0xb801c], byte '^'
	mov [0xb801d], byte 0x1f
	mov [0xb801e], byte ' '

	jmp $

times 2048-($-$$) db 0
