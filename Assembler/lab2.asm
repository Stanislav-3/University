model small
.stack 100h
.data
	string db 6 dup('$')
	overflowMessage db 10, 13, 'Error! Follow the rule: 0 < number < 65536', 10, 13, 'Try again...', 10, 13, '$'
	devidendInputMessage db 10, 13, 'Input a devidend (0 <= devidend < 65536)', 10, 13, '$'
	deviderInputMessage db 10, 13, 'Input a devider (0 < devider < 65536)', 10, 13, '$'
	dividingByZeroMessage db 10, 13, 'Error! Deviding by zero is prohibited!', 10, 13, 'Try again...', 10, 13, '$'
	resultMessage db 'Result:', 10, 13, '$'
	remainderMessage db ',remainder=$'
.code
output proc
   	push ax
	push bx
	push cx
	push dx
	
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
		cycle2:
			mov ah, 01h
			int 21h
			cmp al, 13 ; == enter
			jz enter
			cmp al, 8 ; == backspace
			jz backspace
			cmp al, 27 ; == escape
			jz escape
			cmp al, 48
			jb ignore ; == < '0'
			cmp al, 57
			ja ignore; == > '9'
			jmp next
		ignore:
			call delete
			jmp cycle2
		enter:
			jmp end_cycle2
		backspace:
			mov dl, ''
			mov ah, 02h
			int 21h
			mov ax, bx
			mov bx, 10
			xor dx, dx
			div bx
			mov bx, ax
			call delete
			jmp cycle2
		escape:
			call delete
			escape2:
				cmp bx, 0
				jz cycle2
				mov ax, bx
				xor dx, dx
				mov bx, 10
				div bx
				mov bx, ax; bx /= 10;
				call delete
				jmp escape2
		next:
			sub al, 48
			mov ch, 0;  input digit
			mov cl, al; to cx
			mov ax, bx
			mov dx, 10
			mul dx; ax *= 10
			jc overflow
			add ax, cx; ax += input digit
			jc overflow
			mov bx, ax
			jmp cycle2
		overflow:
			lea dx, overflowMessage
			mov ah, 09h
			int 21h
			jmp begin
		end_cycle2:
			mov ax, bx
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
	jnz correctDividing
	lea dx, dividingByZeroMessage
	mov ah, 09h
	int 21h
	jmp dividerInput
	
	correctDividing:	
	mov bx, ax
	mov ax, cx
	xor dx, dx
	div bx
	
	push dx; remainder to stack
	push ax; quotient to stack
	
	lea dx, resultMessage
	mov ah, 09h
	int 21h
	
	mov ax, cx
	call output; output devidend
	
	mov dl, '/'
	mov ah, 02h 
	int 21h
	
	mov ax, bx
	call output; output devider
	
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