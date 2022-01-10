model small
.stack 100h
.data
	text db 201 dup('0')
	substringLen db -1
	pi db 0, 200 dup('0')
	inputMessage db 10, 13, 'Input substring and a string:', 10, 13, '$'
	overflowMessage db 10, 13, 'String is of a maximum length!$'
	yesMessage db 10, 13, 'yes$'
	noMessage db 10, 13, 'no$'
	spaceNum db 0
.code

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

main:
	mov ax, @data
	mov ds, ax
	mov es, ax
	
	lea dx, inputMessage
	mov ah, 09h
	int 21h
	
	cld; df = 0
	lea di, text
	xor cx, cx
	xor bx, bx
	
	start:
		mov ah, 01h
		int 21h
		
		cmp al, ' '
		jnz other
		cmp spaceNum, 0
		jnz ignore
		cmp cl, 0
		jz ignore
		jmp next
		
		
		abc abc abc
		000 123 4
		
		
		
		other:	
		cmp al, 13
		jz noJump
		cmp al, 10
		jz noJump
		cmp al, 8
		jz backspace
		cmp al, 97
		jb ignore ; == < 'a'
		cmp al, 122
		ja ignore; == > 'z'
		
		jmp next
		
		noJump:
			jmp no
		
		backspace:
			mov dl, ''
			mov ah, 02h
			int 21h
			call delete
			
			cmp cl, 0
			jz start
			
			dec cx
			dec di
			
			cmp cl, substringLen
			jnz string
			mov spaceNum, 0
			mov substringLen, -1
			
			string:
				cmp cl, 0
				jnz notFirst
				xor bx, bx
				jmp start
				
				notFirst:
					lea bx, [pi - 1]
					add bx, cx
					mov bx, [bx]
			jmp start
			
		ignore:
			call delete	
			jmp start
			
		overflow:
			lea dx, overflowMessage
			mov ah, 09h
			int 21h
			jmp no
			
		next:
			cmp cl, 200
			jz overflow
			
			stosb; al to es:di
			
			cmp al, ' '
			jne continue1 ;check several spaces
			mov substringLen, cl
			mov spaceNum, 1
			
		continue1:
			cmp cl, 0
			jnz cycle
			inc cl
			jmp start
			
		cycle: ;while(bl > 0 & text[bl] != al)
			cmp bl, 0
			jz break
			
			lea si, [text + bx]
			cmp [si], al
			jz break
			
			dec bl
			add bx, offset pi
			mov bl, [bx]
			
			jmp cycle
			
		break:
			lea si, [text + bx]
			cmp [si], al
			jne continue2
			inc bl
			
		continue2:
			cmp bl, substringlen
			jz yes
			
			lea si, pi
			xor ch, ch
			add si, cx
			
			mov [si], bx
			
			inc cl
			jmp start

	no:
		lea dx, noMessage
		mov ah, 09h
		
		jmp end
	
	yes:
		lea dx, yesMessage
		mov ah, 09h
	
	end:
		int 21h
	
	mov ah, 4Ch
	int 21h
end main