.286
model small
.stack 100h
.data
;*************************************************** MACROS ***************************************************
	KEY_LEFT equ 4b00h
	KEY_RIGHT equ 4d00h
	KEY_DOWN equ 5000h
	KEY_UP equ 4800h
	KEY_ESC equ 011bh
	KEY_ENTER equ 1c0dh
	DIR_UP equ 0
	DIR_RIGHT equ 1
	DIR_DOWN equ 2
	DIR_LEFT equ 3
;************************************************** VARIABLES *************************************************
	initial_video_mode db ?
	
	sys_handler dd 00
	ticks db 0
	delay db ?
	
	rect_color db ?
	rect_x1 dw ?
	rect_y1 dw ?
	rect_x2 dw ?
	rect_y2 dw ?
	
	tile_color db ?
	tile_x db ?
	tile_y db ?
	tile_w db ?
	x db ?
	y db ?
	max_x dw 320
	max_y dw 200
	
	start_snake_x db 4, 3, 2, 1, 0
	start_snake_y db 0, 0, 0, 0, 0
	start_snake_len dw 5
	
	snake_x db 641 dup (?)
	snake_y db 641 dup (?)
	snake_len dw ?
	max_snake_len dw ?
	tail_x db ?
	tail_y db ?
	snake_color db 4, 639 dup (13, 14, 10, 9)
	
	dir db DIR_RIGHT
	
	candy_x db ?
	candy_y db ?
	candy_color db 11
	need_candy db 1
	
	rand_num db ?
	rand_mod db ?
	
	esc_pressed db 0
	loss db 0
	
	file_read_name db 'config.txt', 0
	file_write_name db 'game_log.txt', 0
	file_handler dw ?
	
	buffer db 255 dup(0), 0
	buff_len dw ?
	num_to_buff dw ?
	str_to_buff dw ?
	str_size dw ?
	
	hard_mode db 'Mode: hard'
	length_text db 'Length: '
	time_text db 11, 13, 'Total seconds: '
	string db 6 dup('$')
	
	min db ?
	sec db ?
	total_time dw ?
	
	romb db 0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0
		 db 0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0
		 db 0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0
		 db 0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0
		 db 0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0
		 db 0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0
		 db 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0
		 db 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0
		 db 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
		 db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		 db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		 db 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
		 db 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0
		 db 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0
		 db 0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0
		 db 0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0
		 db 0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0
		 db 0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0
		 db 0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0
		 db 0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0
		 
	star db 1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1
		 db 0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0
		 db 0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0
		 db 0,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,0
	 	 db 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0
	  	 db 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0
	     db 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0
		 db 0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0
		 db 0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0
		 db 1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1
		 db 1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1
		 db 0,0,1,1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,0,0
	 	 db 0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0
		 db 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0
		 db 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0
		 db 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0
		 db 0,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,0
		 db 0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0
		 db 0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0
		 db 1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1
		 
	mode db ?
;*************************************************** CODE *****************************************************
.code
LOCALS
;*********************************************** DRAWING THING ************************************************
fill_rect proc
	push ax
	push bx
	push cx
	push dx
	
    mov ah, 0ch
    mov bx, 00h
    mov al, rect_color
    mov cx, rect_x1
    mov dx, rect_y1
	@@cycle:
		int 10h
		inc cx
		cmp cx, rect_x2
		jnz @@cycle
		mov cx, rect_x1
		inc dx
		cmp dx, rect_y2
		jnz @@cycle
	
	pop dx
	pop cx
	pop bx
	pop ax
	ret
fill_rect endp

fill_romb proc
	push ax
	push bx
	push cx
	push dx
	push si
	
	xor si, si
	
	mov ah, 0ch
	mov bx, 00h
	mov al, rect_color
	mov cx, rect_x1
	mov dx, rect_y1
	
	@@cycle:
		cmp romb[si], 1
		jnz @@not_color
		int 10h
		
		@@not_color:
		inc si
		inc cx
		cmp cx, rect_x2
		jnz @@cycle
		
		mov cx, rect_x1
		inc dx
		cmp dx, rect_y2
		jnz @@cycle
		
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	ret
fill_romb endp

fill_star proc
	push ax
	push bx
	push cx
	push dx
	push si

	xor si, si

	mov ah, 0ch
	mov bx, 00h
	mov al, rect_color
	mov cx, rect_x1
	mov dx, rect_y1

	@@cycle:
		cmp star[si], 1
		jnz @@not_color
		int 10h
		
		@@not_color:
		inc si
		inc cx
		cmp cx, rect_x2
		jnz @@cycle
	
		mov cx, rect_x1
		inc dx
		cmp dx, rect_y2
		jnz @@cycle
	
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		ret
fill_star endp

fill_tile proc
	push ax
	push bx
	
	mov al, tile_color
	mov rect_color, al
	

	xor ax, ax
	xor bx, bx
	mov bl, tile_w
	
	mov al, tile_x
	mul bl
    mov rect_x1, ax
    add ax, bx
    mov rect_x2, ax
	
    mov al, tile_y
    mul bl
    mov rect_y1, ax
    add ax, bx
    mov rect_y2, ax
	
	cmp mode, 0
	jz @@rect
	
	cmp mode, 1
	jz @@romb
	
	jmp @@star
	
	@@rect:
		call fill_rect
		jmp @@return
	
	@@romb:
		call fill_romb
		jmp @@return
		
	@@star:	
		call fill_star
	
	@@return:
	pop bx
	pop ax
	ret
fill_tile endp

;******************************************** END DRAWING THING **********************************************

;************************************************ SNAKE THING ************************************************ 

display_snake proc
	push ax
	push bx
	push si
	
	mov si, 0
	mov bx, snake_len
	dec bx
	@@cycle:
		xor ax, ax
		
		mov al, [snake_x[si]]
		mov tile_x, al
		cmp al, candy_x
		jnz @@next
		inc ah
		
		@@next:
		mov al, [snake_y[si]]
		mov tile_y, al
		cmp al, candy_y
		jnz @@next2
		inc ah
		
		;setting color and eating stuff
		@@next2:	
		cmp ah, 2
		jnz @@not_digestion_tile
	
		cmp si, 0
		jnz @@digest
		;if head
		jmp @@not_digestion_tile
		
		@@digest:
			mov al, candy_color
			mov tile_color, al
			
			;if tail
			cmp si, bx
			jnz @@next3
			mov need_candy, 1
			inc snake_len
			
			@@next3:
			jmp @@fill_tile
			
		@@not_digestion_tile:
		mov al, [snake_color[si]]
		mov tile_color, al
		
		@@fill_tile:
		call fill_tile
		inc si
		cmp snake_len, si
		jnz @@cycle
    
	pop si
	pop bx
	pop ax
	ret
display_snake endp

update_snake proc
	push ax
	push bx
	push cx
	push si
	push di
	
	mov cx, snake_len
	mov si, cx
	mov di, cx
	dec si
	
	cmp cx, max_snake_len
	jnz @@not_win
	
	;win
    mov rect_x1, 0
    mov rect_y1, 0
    mov rect_x2, 320
    mov rect_y2, 200
    mov al, candy_color
    mov rect_color, al
    call fill_rect
	;snake will not be displayed & user reaction is being waited
	mov loss, 1
		
	@@not_win:
	mov bl, [snake_x[si]]
	mov tail_x, bl
	mov bl, [snake_y[si]]
	mov tail_y, bl
	
	@@cycle:
    	mov al, snake_x[si]
    	mov snake_x[di], al
    	mov al, snake_y[si]
    	mov snake_y[di], al
		dec si
		dec di
		loop @@cycle
	
	cmp dir, DIR_UP
	jz @@up
	cmp dir, DIR_RIGHT
	jz @@right
	cmp dir, DIR_DOWN
	jz @@down
	jmp @@left
	
	@@up:
		dec snake_y
		jmp @@return
	@@right:
		inc snake_x
		jmp @@return
	@@down:
		inc snake_y
		jmp @@return
	@@left:
		dec snake_x
	
	@@return:
	call delete_snake
	call display_snake
	
	cmp need_candy, 1
	jnz @@not_need_candy
		call new_candy
		mov need_candy, 0
	
	@@not_need_candy:
	pop di
	pop si
	pop cx
	pop bx
	pop ax
	ret
update_snake endp

update_dir proc
	push ax
	
	@@cycle:
    	mov ah, 01h
    	int 16h
		jz @@return
		
        mov ah, 00h
        int 16h
		
		cmp ax, KEY_UP
		jz @@up
		cmp ax, KEY_RIGHT
		jz @@right
		cmp ax, KEY_DOWN
		jz @@down
		cmp ax, KEY_LEFT
		jz @@left
	    cmp ax, KEY_ESC
	    jz @@esc
		
		jmp @@cycle
		
		@@up:
			cmp dir, DIR_DOWN
			jz @@return
			mov dir, DIR_UP
			jmp @@return
		@@right:
			cmp dir, DIR_LEFT
			jz @@return
			mov dir, DIR_RIGHT
			jmp @@return
		@@down:
			cmp dir, DIR_UP
			jz @@return
			mov dir, DIR_DOWN
			jmp @@return
		@@left:
			cmp dir, DIR_RIGHT
			jz @@return
			mov dir, DIR_LEFT
			jmp @@return
		@@esc:
			mov esc_pressed, 1
			
	@@return:
	pop ax
	ret
update_dir endp

delete_snake proc
	push ax
	push si
	
	mov si, snake_len
	@@cycle:
		mov al, [snake_x[si]]
		mov tile_x, al
		mov al, [snake_y[si]]
		mov tile_y, al	
		mov al, 0
		mov tile_color, al
		call fill_tile
		
		dec si
		cmp si, -1
		jnz @@cycle
		
		;remove this thing
		mov al, tail_x
		mov tile_x, al
		mov al, tail_y
		mov tile_y, al	
		mov al, 0
		mov tile_color, al
		call fill_tile
	pop si
	pop ax
	ret
delete_snake endp

check_collision proc
	push ax
	push si
	
	mov ah, snake_x
	mov al, snake_y
	
	;horizontal borders check
	cmp ah, x
	jb @@continue
	jmp @@yes
	@@continue:
	
	;vertical borders check
	cmp al, y
	jb @@continue1
	jmp @@yes
	@@continue1:
	
	;self-collision check
	mov si, snake_len
	
	@@cycle:
		dec si
		cmp si, 3
		jz @@return
		
		cmp ah, [snake_x[si]]
		jnz @@cycle
		cmp al, [snake_y[si]]
		jz @@yes
		jmp @@cycle

	@@yes:
		mov loss, 1
	
        mov rect_x1, 0
        mov rect_y1, 0
        mov rect_x2, 320
        mov rect_y2, 200
        mov al, snake_color
        mov rect_color, al
        call fill_rect
		
		call check_new_game
		
	@@return:
	pop si
	pop ax
	ret
check_collision endp

;********************************************** END SNAKE THING ********************************************** 

;*********************************************** NEW GAME THING ********************************************** 

check_new_game proc
	push ax
	
	cmp loss, 0
	jz @@return
	
    mov ah, 01h
    int 16h
    jz @@return
    
    mov ah, 00h
    int 16h
    
    cmp ax, KEY_ENTER
    jz @@enter
    
    cmp ax, KEY_ESC
    jz @@esc
    
	jmp @@return
	
    @@enter:
        call new_game_init
        jmp @@return
    @@esc:
        mov esc_pressed, 1
        
	@@return:
	pop ax
	ret
check_new_game endp

new_game_init proc
	push si	
	push ax
	push bx
	push dx
	
	mov loss, 0
	mov need_candy, 1
	
    mov rect_x1, 0
    mov rect_y1, 0
    mov rect_x2, 320
    mov rect_y2, 200
    mov al, 0
    mov rect_color, al
    call fill_rect
	
	call randomize
	call file_read
	
	;x init
	xor dx, dx
	xor bx, bx
	mov ax, max_x
	mov bl, tile_w
	div bx
	mov x, al

	;y init
	xor bx, bx
	mov bl, tile_w
	mov ax, max_y
	div bl
	mov y, al
	
	;dir init
	mov dir, DIR_RIGHT

	;len init
	mov bx, start_snake_len
	mov snake_len, bx
	
	;snake init
	mov si, bx
	@@cycle:
		dec si
		mov al, start_snake_x[si]
		mov snake_x[si], al
		mov al, start_snake_y[si]
		mov snake_y[si], al
		cmp si, 0
		jnz @@cycle
		
	mov al, x
	mul y
	mov max_snake_len, ax
	
	pop dx
	pop bx
	pop ax
	pop si
	ret
new_game_init endp

;******************************************** END NEW GAME THING ********************************************* 

;************************************************ CANDY THING ************************************************ 

randomize proc
	push ax
	push cx
	push dx

    mov ah, 2ch
    int 21h
    mov rand_num, dl

	pop dx
	pop cx
	pop ax
    ret
randomize endp

rand proc
	push ax
	
    mov al, rand_num
	call randomize
	add al, rand_num
	div rand_mod
	mov rand_num, ah
	
	pop ax
    ret
rand endp

new_candy proc
	push ax
	push si
	push di
	
	xor di, di
	@@new_candy:
		xor ax, ax
		
		add rand_num, 1
		inc di
		
		mov al, x
		mov rand_mod, al
		call rand
		mov al, rand_num
		mov candy_x, al
	
		mov al, y
		mov rand_mod, al
		call rand
		mov al, rand_num
		mov candy_y, al
		
		;checking collision (snake & candy)
		mov si, snake_len
		mov ah, candy_x
		mov al, candy_y
		@@check:
			cmp si, 0
			jz @@alright
			cmp di, 1000
			jz @@alright
			
			dec si

			cmp ah, [snake_x[si]]
			jnz @@check
			
			cmp al, [snake_y[si]]
			jz @@new_candy
			
			jmp @@check
			
		@@alright:
		mov al, candy_x
		mov tile_x, al
		mov al, candy_y
		mov tile_y, al
		mov al, candy_color
		mov tile_color, al
		call fill_tile
	
	pop di
	pop si
	pop ax
	ret
new_candy endp

;************************************************ END CANDY THING ******************************************** 

;************************************************** FILE THING ***********************************************
file_write proc
	pusha
	
	;create file
	mov ah, 3ch
	mov cx, 0
	lea dx, file_write_name
	int 21h
	;if error
	jc @@return
	
	;open file
	mov ah, 3dh
	mov al, 1
	lea dx, file_write_name
	int 21h
	;if error
	jc @@return
	
	mov file_handler, ax
	
	;build a string to write
	call flush_buff
	
	lea ax, length_text
	mov str_to_buff, ax
	mov str_size, 8
	call string_to_buff
	
	call update_buff_len
	
	mov ax, snake_len
	mov num_to_buff, ax
	call number_to_buff
	
	call update_buff_len
	
	lea ax, time_text
	mov str_to_buff, ax
	mov str_size, 17
	call string_to_buff
	
	call update_buff_len
	
	call get_total_time
	
	mov ax, total_time
	mov num_to_buff, ax
	call number_to_buff
	
	call update_buff_len
	
	@@write:
	;write a string
	mov ah, 40h
	mov bx, file_handler
	mov cx, buff_len
	lea dx, buffer
	int 21h
		
	@@return:
	;close
	mov ah, 3eh
	lea bx, file_handler
	int 21h
	
	popa
	ret
file_write endp

string_to_buff proc
	push cx
	push si
	push di

	lea di, buffer
	add di, buff_len
	mov si, str_to_buff
	mov cx, str_size
	
	repe movsb

	@@return:	
	pop di
	pop si
	pop cx
	ret
string_to_buff endp

number_to_buff proc
	pusha
	
	call update_buff_len
	xor si, si
	
	lea bx, [string + 5]	
	mov ax, num_to_buff
	mov cx, 10
	cycle1:
		xor dx, dx
		div cx
		dec bx
		add dx, '0'
		mov [bx], dl
		inc si
		cmp ax, 0
	jnz cycle1
	
	mov ax, buff_len
	
	;len digits amount
	mov cx, si
	
	;len to buff
	lea di, buffer
	add di, buff_len
	mov si, bx

	repe movsb
	
	popa
	ret
number_to_buff endp

update_buff_len proc
	push ax
	push cx
	push di
	
	xor cx, cx
	mov al, 1
	lea di, buffer
	@@cycle:
		scasb
		jnc @@return
		inc cx
		jmp @@cycle
	
	@@return:
	mov buff_len, cx
	
	pop di
	pop cx
	pop ax	
	ret
update_buff_len endp

flush_buff proc
	push ax
	push si
	push di
	
	lea di, buffer
	mov al, 0
	@@cycle:
		scasb
		jz @@return
		dec di
		stosb
		jmp @@cycle
	
	mov buff_len, 0
	@@return:
	pop di
	pop si
	pop ax
	ret
flush_buff endp

file_read proc
	pusha
	
	;open
	mov ah, 3dh
	mov al, 0
	lea dx, file_read_name
	int 21h
	;if error
	jc @@normal
	
	mov file_handler, ax
	
	;read
	mov ah, 3Fh
	mov bx, file_handler
	mov cx, 10
	lea dx, buffer
	int 21h
	
	;close
	mov ah, 3eh
	lea bx, file_handler
	int 21h
	
	;cmp if hard mode is set
	mov cx, 10
	lea si, buffer
	lea di, hard_mode
	repe cmpsb 
	jne @@normal
	
	@@hard:
		mov delay, 1
		mov tile_w, 10
		jmp @@return
		
	@@normal:
		mov delay, 5
		mov tile_w, 20
	
	@@return:
	popa
	ret
file_read endp

;************************************************ END FILE THING *********************************************

;************************************************** TIME THING ***********************************************

get_time proc
	push ax
	push cx
	push dx

	mov ah, 2ch
	int 21h
	
	mov min, cl
	mov sec, dh

	pop dx
	pop cx
	pop ax
	ret
get_time endp

get_total_time proc
	push ax
	push bx
	
	xor ax, ax
	
	mov al, min
	mov bl, sec
	call get_time
	
	cmp al, min
	jna @@next
	add min, 60
	@@next:
	sub min, al
	
	mov al, bl
	
	cmp al, sec
	jna @@next2
	dec min
	add sec, 60
	@@next2:
	sub sec, al
	
	mov al, min
	mov ah, 60
	mul ah
	
	add al, sec
	mov total_time, ax
	
	pop bx
	pop ax
	ret
get_total_time endp

;************************************************ END TIME THING *********************************************

;************************************************* HANDLER THING *********************************************

set_my_handler proc
	push es
	push ds
	
	mov ax, 351ch
	int 21h
	mov word ptr sys_handler, bx
	mov word ptr sys_handler + 2, es
	
	mov ax, 251ch
	mov dx, @code
	mov ds, dx
	mov dx, offset my_handler
	int 21h
	
	pop ds
	pop es
	ret
set_my_handler endp

set_sys_handler proc
	push ds
	
	mov ax, 251ch
	mov dx, word ptr sys_handler
	mov bx, word ptr sys_handler + 2
	mov ds, bx
	int 21h
	
	pop ds
	ret
set_sys_handler endp

my_handler proc
	cli

	inc ticks
	mov al, ticks
	cmp al, delay
	jnz @@return
	
	mov ticks, 0
	
	cmp loss, 1
	jz @@not_display
	
	call update_dir
	call update_snake
	call check_collision
	
	@@not_display:
		call check_new_game
		
	@@return:
	sti
	iret
my_handler endp

;************************************************ END HANDLER THING ********************************************

;****************************************************** MAIN ***************************************************

main:
	mov ax, @data
	mov ds, ax
	mov es, ax
	call new_game_init
	call get_time
	
	mov ah, 0fh
	int 10h
	mov initial_video_mode, al
	
	;set video mode
    mov ax, 13h
    int 10h
	
	mov mode, 2
	
	call set_my_handler
	@@cycle:
		cmp esc_pressed, 1
		jne @@cycle
	
	;exit
	call file_write
	call set_sys_handler
	
	mov ah, 00h
	mov al, initial_video_mode
	int 10h
	
	mov ah, 4ch
	int 21h
end main

;**************************************************** END MAIN ************************************************