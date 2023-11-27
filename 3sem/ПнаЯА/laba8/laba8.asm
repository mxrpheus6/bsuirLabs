.186
.model tiny               
.code        
              
	org 100h    
    start:

        jmp main

        command_line_text              db 128 dup(0)
        command_line_buffer            db 3 dup('$')

        arguments_count                db 0

        message_arguments_error        db "Wrong arguments. Try: 'laba8.com hour min sec hour min sec$"
        message_hour_error             db "Wrong time number. Hour is in range from 0 to 23$"
        message_min_sec_error          db "Wrong time number. Minutes and seconds are in range from 0 to 59$"
        message_overflow               db "Overflow detected!$"
        message_not_digit              db "There are not digits in your arguments!$"
        
        alarm_status                   db 0     ;0 - off, 1 - on

        ;time
        stop_hour               db 0 
        stop_min                db 0
        stop_sec                db 0

        signal_duration_hour    db 0
        signal_duration_min     db 0
        signal_duration_sec     db 0

        final_hour              db 0
        final_min               db 0
        final_sec               db 0

        ;banner
        width_banner        equ 40
        width_dos           equ 80
        yellow              equ 6020h
        white               equ 7020h
        black               equ 0020h

        alarm_banner 	dw 2 * width_banner dup(yellow)
                        dw 6 dup(yellow), 3 dup(white), 2 dup(yellow), white, 6 dup(yellow), 3 dup(white), 2 dup(yellow), 5 dup(white), 2 dup(yellow), white, 3 dup(yellow), white, 5 dup(yellow)
                        dw 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 4 dup(yellow), white, yellow, 2 dup(white), yellow, 2 dup(white), 5 dup(yellow)
                        dw 5 dup(yellow), 5 dup(white), yellow, white, 5 dup(yellow), 5 dup(white), yellow, 5 dup(white), 2 dup(yellow), white, yellow, white, yellow, white, 5 dup(yellow)
                        dw 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 2 dup(yellow), white, 3 dup(yellow), white, 3 dup(yellow), white, 5 dup(yellow)
                        dw 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 3 dup(yellow), white, 2 dup(yellow), white, 3 dup(yellow), white, 5 dup(yellow)
                        dw 5 dup(yellow), white, 3 dup(yellow), white, yellow, 5 dup(white), yellow, white, 3 dup(yellow), white, yellow, white, 4 dup(yellow), white, yellow, white, 3 dup(yellow), white, 5 dup(yellow)
			            dw 2 * width_banner dup(yellow)

        clear_banner	dw width_banner dup(black)
			            dw width_banner dup(black)
			            dw width_banner dup(black)
			            dw width_banner dup(black)
			            dw width_banner dup(black) 
			            dw width_banner dup(black)
			            dw width_banner dup(black)
                        dw width_banner dup(black)
                        dw width_banner dup(black)
                        dw width_banner dup(black)    
        
        int_old_handler dd 0

        handler PROC
            pushf

            call cs:int_old_handler
            push ds
            push es
            push ax
            push bx
            push cx
            push dx
            push di

            push cs
            pop ds

            mov ah, 02h         ;ch - часы в , cl - минуты, dh - секунды. (например CX = 1243h = 12:43)
            int 1Ah

            cmp ch, stop_hour       ;проверка на возможность включения
            jne stop_check
            cmp cl, stop_min
            jne stop_check
            cmp dh, stop_sec
            jne stop_check

            mov dl, alarm_status
            cmp dl, 0
            jne stop_check

            push ax
            push dx

            xor ax, ax
            xor dx, dx

            mov dl, 07h
            mov ah, 02h
            int 21h

            pop dx
            pop ax

            lea si, alarm_banner
            call print_banner
            mov dl, 1
            mov alarm_status, dl

            jmp end_handler

            stop_check:
                cmp ch, final_hour
                jne end_handler
                cmp cl, final_min
                jne end_handler
                cmp dh, final_sec
                jne end_handler

                mov dl, alarm_status
                cmp dl, 1
                jne end_handler

                lea si, clear_banner
                call print_banner
                mov dl, 0
                mov alarm_status, 0

            end_handler:
                pop di
                pop dx
                pop cx
                pop bx
                pop ax
                pop es
                pop ds
                iret
        handler ENDP   

        print_banner PROC  
            push es

            push ax
            mov ax, 0B800h                          
            mov es, ax
            pop ax                      
                                           
            mov di, 9 * width_dos * 2 + (width_dos - width_banner) 
            mov cx, 10                         
            loopPrintBanner:                     
                push cx
                                                
                mov cx, width_banner
                rep movsw                         
                                            
                add di, 2 * (width_dos - width_banner)
                                            
                pop cx                          
                loop loopPrintBanner
             
            pop es                          
            ret                               
        print_banner ENDP  

        output_string PROC
            push bp
            mov bp, sp

            mov ah, 09h
            mov dx, [bp + 4]
            int 21h

            pop bp
            ret 2
        output_string ENDP

        convert_to_hex PROC
            push bp
            mov bp, sp     ;[bp + 4] string_num
            
            push bx
            push si

            mov si, [bp + 4]

            parse_loop:

                xor bx, bx
                mov bl, [si]

                cmp bl, 24h
                je converted

                sub bl, 30h
                cmp bl, 0
                jb handle_not_digit
                cmp bl, 9
                ja handle_not_digit

                push bx
                mov bx, 0Ah
                imul bx
                pop bx
                jo handle_overflow
                xor bh, bh
                add ax, bx
                jo handle_overflow 

                inc si
                jmp parse_loop

            converted:
                pop si
                pop bx
                pop bp
                ret 2

            handle_not_digit:
                mov ah, 09h
                lea dx, message_not_digit
                int 21h
                jmp exit
                
            handle_overflow:
                mov ah, 09h
                lea dx, message_overflow
                int 21h
                jmp exit
        convert_to_hex ENDP

        parse_element PROC
            push bp
            mov bp, sp  ;[bp + 4] - variable
                        ;[bp + 6] - message error
                        

            push ax
            push bx

            parse_stop_time:
                cmp BYTE PTR es:[si], 0Dh
                je check
                cmp BYTE PTR es:[si], ' '
                je result_stop_time

                mov al, es:[si]
                mov [di + bx], al

                inc si
                inc bx
                jmp parse_stop_time

            check:
                cmp arguments_count, 5
                jne wrong_arguments

            result_stop_time:
                mov al, '$'
                mov [di + bx], al

                xor ax, ax
                push di
                call convert_to_hex

                push si
                mov si, [bp + 4]
                mov [si], ax
                pop si
                inc arguments_count
                jmp parsed

            wrong_arguments:
                lea dx, message_arguments_error
                push dx
                call output_string
                jmp exit

            parsed:
                pop bx
                pop ax
                pop bp
                ret 4
        parse_element ENDP   

        parse_time PROC
            push bp
            mov bp, sp

            push ax
            push bx
            push cx
            push dx
            push si
            push di

            mov cl, es:[80h] ;CLA length
            add cx, 80h      ;last symbol
            mov si, 82h      ;first symbol
            lea di, command_line_buffer

            mov bx, 0   ;j = 0

            lea dx, message_hour_error
            push dx
            lea dx, stop_hour
            push dx
            call parse_element

            inc si      ;i++
            mov bx, 0   ;j = 0

            lea dx, message_min_sec_error
            push dx
            lea dx, stop_min
            push dx
            call parse_element

            inc si      ;i++
            mov bx, 0   ;j = 0

            lea dx, message_min_sec_error
            push dx
            lea dx, stop_sec
            push dx
            call parse_element

            inc si      ;i++
            mov bx, 0   ;j = 0

            lea dx, message_hour_error
            push dx
            lea dx, signal_duration_hour
            push dx
            call parse_element

            inc si      ;i++
            mov bx, 0   ;j = 0

            lea dx, message_min_sec_error
            push dx
            lea dx, signal_duration_min
            push dx
            call parse_element

            inc si      ;i++
            mov bx, 0

            lea dx, message_min_sec_error
            push dx
            lea dx, signal_duration_sec
            push dx
            call parse_element

            pop di
            pop si
            pop dx
            pop cx
            pop bx
            pop ax
            pop bp
                
            ret 
        parse_time ENDP   

        calcucate_final_time PROC
            push ax
            push bx

	        xor ah, ah                          ; sec
	        mov al, stop_sec                    
	        add al, signal_duration_sec         ; duration
	        mov bl, 60			                
	        div bl                              ; частное - al, остаток - ah
	        mov final_sec, ah                  

            xor ah, ah
            add al, stop_min
            add al, signal_duration_min
            mov bl, 60
            div bl
            mov final_min, ah

            xor ah, ah
            add al, stop_hour
            add al, signal_duration_hour
            mov bl, 24
            div bl
            mov final_hour, ah

            pop bx
            pop ax
            ret
        calcucate_final_time ENDP

        convert_hex_to_bcd PROC
            push ax
            push bx
            push cx
            push dx
            push si

            mov cx, 9
            mov bl, 10

            lea si, stop_hour

            convert_loop:
                xor ah, ah
                mov al, [si]
                div bl      ;al - чаcтное ah - остаток

                mov dl, al

                shl dl, 4

                add dl, ah
                mov [si], dl

                inc si
                loop convert_loop


                pop si
                pop dx
                pop cx
                pop bx
                pop ax
                ret
        convert_hex_to_bcd ENDP

        set_handler PROC
            push ax
            push bx
            push dx

            cli                         ;запрет прерываний

            mov ah, 35h                 ;получаем адрес обработчика
            mov al, 1Ch                 ;номер прерывания
            int 21h                     ;bx = 0000:[AL * 4] - смещение обработчика es = 0000:[(AL*4) + 2] - сегментный адрес

            mov word ptr [offset int_old_handler], bx
            mov word ptr [offset int_old_handler + 2], es

            push ds
            pop es                      ;настройка регистра ds на данные резидентной программ

            mov ah, 25h                 ;функция замены обработчика
            mov al, 1Ch                 
            lea dx, handler
            int 21h

            sti                         ;разрешение прерываний

            pop dx
            pop bx
            pop ax
            ret
        set_handler ENDP 

        main:
            call parse_time

            call calcucate_final_time

            call convert_hex_to_bcd

            call set_handler

            mov ah, 31h
            mov al, 0

            mov dx, (output_string - start + 100h) / 16 + 16 / 16

            int 21h

        exit:
            int 20h
    end start