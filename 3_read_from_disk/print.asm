PrintString:
	mov ah, 0x0e
	.Loop:
		cmp [bx], byte 0
		je .Exit
		mov al, [bx]
		int 0x10
		inc bx
		jmp .Loop
	.Exit:
	ret

;TestString:
;	db "0x03: This is a test string", 0

