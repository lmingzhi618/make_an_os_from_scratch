gdt_nulldesc:
	dd 0
	dd 0

gdt_codedesc:
	dw 0xffff	; limit:		0:15
	dw 0x0000	; Base16:		16:31
	db 0x00		; Base8:		16:23
	db 10011010b; Access Byte:	Pr|Privl(2)|S|Ex|DC|RW|Ac	
	db 11001111b; Flags + Upper Limit
	db 0x00		; Base8:		56:63
gdt_datadesc:
	dw 0xffff	
	dw 0x0000	
	db 0x00		
	db 10010010b	
	db 11001111b
	db 0x00		

gdt_end:

gdt_descriptor:
	gdt_size: 
		dw gdt_end - gdt_nulldesc - 1
		dd gdt_nulldesc

codeseg equ gdt_codedesc - gdt_nulldesc
dataseg equ gdt_datadesc - gdt_nulldesc
