PROGRAM_SPACE equ 0x7e00

ReadDisk:
	mov ah, 0x02	; BIOS function for reading disk
	mov bx, PROGRAM_SPACE
	mov al, 4
	mov dl, [BOOT_DISK]
	mov ch, 0x00	; cylinder 0
	mov dh, 0x00	; head 0
	mov cl, 0x02	; sector 2
	
	int 0x13		; interupt code for read from disk

	jc DiskReadFailed
	ret

BOOT_DISK:
	db 0

DiskReadErrorString:
	db "Disk read failed",0

DiskReadFailed:
	mov bx, DiskReadErrorString
	call PrintString

	jmp $
