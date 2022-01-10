model small
.stack 100h
.data
	a dw 1
	b dw 2
	c dw 3
	d dw 4
.code
main:
	mov ax, @data
	mov ds, ax

	;a&d
	mov ax, a
	and ax, d
	;b+c
	mov bx, b
	add bx, c
	;if overflow
	jc false2
	;if (a&d) == (b+c)
	CMP ax, bx
	jnz false1
	;true1
		mov ax, a
		xor ax, b
		mov bx, b
		or bx, d
		add ax, bx
		jmp ending
	false1:
		;a|d
		mov ax, a
		or ax, d
		;b+c
		;if (a|d) == (b+c)
		CMP ax, bx
		jnz false2
		;true2
			mov ax, a
			or ax, c
			mov bx, b
			xor bx, d
			or ax, bx
			jmp ending
		false2:
			mov ax, a
			add ax, c
			mov bx, b
			add bx, d
			or ax, bx 
	ending:
	mov ah, 4Ch
	int 21h
end main