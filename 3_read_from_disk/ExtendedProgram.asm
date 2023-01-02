[org 0x7e00]

mov bx, ExtendedSpaceSuccess
call PrintString

jmp $

%include "print.asm"

ExtendedSpaceSuccess:
	db "We are successfully in extended space.", 0

times 2048-($-$$) db 0
