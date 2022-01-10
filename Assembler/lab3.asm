model small
.stack 100h
.data
	string db 6 dup('$')
	overflowMessage db 10, 13, 'Error! Follow the rule: -32768 <= number <= 32767', 10, 13, 'Try again...', 10, 13, '$'
	devidendInputMessage db 10, 13, 'Input a dividend (-32768 <= number <= 32767)', 10, 13, '$'
	deviderInputMessage db 10, 13, 'Input a divider (-32768 <= number <= 32767)', 10, 13, '$'
	errorMessage db 10, 13, 'Error!', 10, 13, 'Try again...', 10, 13, '$'
	resultMessage db 'Result:', 10, 13, '$'
	remainderMessage db ',remainder=$'
.code
output proc
   	push ax
	push bx
	push cx
	push dx
	
	test ax, ax
	jns positive
	push ax
	mov dl, '-'
	mov ah, 02h
	int 21h
	pop ax
	neg ax
	
	positive:
	lea bx, [string + 5]	
	;ax to string
	mov cx, 10
	cycle1:
		xor dx, dx
		div cx
		dec bx
		add dx, '0'
		mov [bx], dl
		cmp ax, 0
	jnz cycle1
	
	;output string
	lea dx, [bx]
	mov ah, 09h
	int 21h
	
	pop dx
	pop cx
	pop bx
	pop ax
	ret
output endp

;deletes a symbol in console
delete proc
	push dx
	push ax
	
	mov dl, 08; == 'backspace'
	mov ah, 02h; carriege to left
	int 21h
	
	mov dl, 32; == 'space'
	mov ah, 02h; insert space
	int 21h
	
	mov dl, 08; == 'backspace'
	mov ah, 02h; carriege to left
	int 21h
	
	pop ax
	pop dx
	ret
delete endp

input proc
	push bx
	push cx
	push dx
	begin:
		xor bx, bx
		xor si, si
		cycle2:
			mov ah, 01h
			int 21h
			cmp al, 13 ; == enter
			jz enter
			cmp al, 8 ; == backspace
			jz backspace
			cmp al, 27 ; == escape
			jz escape
			cmp al, '-'
			jz checkSign
			cmp al, 48
			jb ignore ; == < '0'
			cmp al, 57
			ja ignore; == > '9'
			jmp next
		checkSign:
			cmp bx, 0
			jnz ignore
			cmp si, 0
			jnz ignore
			mov si, 1
			jmp cycle2
		ignore:
			call delete
			jmp cycle2
		enter:
			jmp end_cycle2
		backspace:
			mov dl, ''
			mov ah, 02h
			int 21h
			call delete
			cmp bx, 0
			jnz continue2
			;cmp si, 1
			;jnz cycle2; number < 0
			jmp begin
			continue2: 
				mov ax, bx
				mov bx, 10
				xor dx, dx
				div bx
				mov bx, ax
				cmp bx, 0
				jnz cycle2
				cmp si, 2
				jnz cycle2
				jmp begin
		escape:
			call delete
			escape2:
				cmp bx, 0
				jz negative
				mov ax, bx
				xor dx, dx
				mov bx, 10
				div bx
				mov bx, ax; bx /= 10;
				call delete
				jmp escape2
			negative:
				cmp si, 1
				jz c
				jmp begin
				c:
				call delete
				jmp begin
		next:
			cmp al, '0'
			jnz continue3
			cmp bx, 0
			jnz continue3
			cmp si, 1
			jz ignore
			continue3:
				cmp si, 0
				jnz continue4
				mov si, 2
				continue4:
				sub al, '0'
				mov ch, 0;  input digit
				mov cl, al; to cx
				mov ax, bx
				mov dx, 10
				mul dx; ax *= 10
				jo overflow
				test ax, 1000000000000000b;check if first bit is 1
				jnz overflow
				add ax, cx; ax += input digit
				jno continue
				cmp ax, 1000000000000000b;check if number is 32768
				jnz overflow
				cmp si, 1; check if number < 0
				jz continue
				jmp overflow
			continue:
				mov bx, ax
				jmp cycle2
		overflow:
			lea dx, overflowMessage
			mov ah, 09h
			int 21h
			jmp begin
		end_cycle2:
			mov ax, bx
			cmp si, 1
			jnz endInput
			neg ax
	endInput:
	pop dx
	pop cx
	pop bx	
	ret
input endp

main:
	mov ax, @data
	mov ds, ax
	
	lea dx, devidendInputMessage
	mov ah, 09h
	int 21h
	call input
	mov cx, ax; devidend to cx
	
	dividerInput:
	lea dx, deviderInputMessage
	mov ah, 09h
	int 21h
	call input; devider to ax
	
	cmp ax, 0; dividing by zero
	jz incorrectDividing
	cmp ax, -1;
	jnz correctDividing
	cmp cx, -32768
	jnz correctDividing	
	incorrectDividing:
		lea dx, errorMessage
		mov ah, 09h
		int 21h
	jmp dividerInput
	
	correctDividing:	
	mov bx, ax
	mov ax, cx
	cwd
	idiv bx
	
	push dx; remainder to stack
	push ax; quotient to stack
	
	lea dx, resultMessage
	mov ah, 09h
	int 21h
	
	mov ax, cx
	call output; output dividend
	
	mov dl, '/'
	mov ah, 02h 
	int 21h
	
	mov ax, bx
	call output; output divider
	
	mov dl, '='
	mov ah, 02h 
	int 21h
	
	pop ax
	call output; output quotient
	
	pop ax
	mov bx, ax
	cmp ax, 0
	jz end
	lea dx, remainderMessage
	mov ah, 09h
	int 21h
	mov ax, bx
	call output; output remainder
	
	end:
	mov ah, 4Ch
	int 21h
end main