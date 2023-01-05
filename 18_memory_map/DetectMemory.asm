MemoryRegionCount:
	db 0
	GLOBAL MemoryRegionCount

; Reference: https://uefi.org/htmlspecs/ACPI_Spec_6_4_html/15_System_Address_Map_Interfaces/int-15h-e820h---query-system-address-map.html
DetectMemory:
	mov ax, 0
	mov es, ax
	mov di, 0x5000
	mov edx, 0x534d4150 ; "SMAP"
	xor ebx, ebx

	.loop:
		mov eax, 0xE820
		mov ecx, 24
		int 0x15

		cmp ebx, 0
		je .finished

		add di, 24
		inc byte [MemoryRegionCount]
		jmp .loop

	.finished:
	ret
