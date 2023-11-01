.8086

.model small

.stack 100h

.data
    message_arguments_error     db "Wrong arguments. Try: laba5 file_name.txt$"
    message_file_missing        db "Can't open file. Probably it's missing$"
    message_success             db "Amount of strings with your word is $"
    
    message_input_word          db "This program counts strings with your word. Please enter the word:$"
    word_to_find                db 128 dup('$')
    word_buffer                 db 128 dup('$')

    counter                     dw 0

    file_name                   db 128 dup(0)
    file_buffer                 db 1024 dup('$')    
    file_buffer_size            equ 1024
    file_descriptor             dw 0

    number_buffer db 9 dup("$")
    
    crlf                        db 0Dh, 0Ah, '$'
.code

    input_string PROC
        push bp
        mov bp, sp

        mov ah, 0Ah
        mov dx, [bp + 4]
        int 21h

        mov bx, offset dx
        mov ax, [bx + 1]
        xor ah, ah
        add bx, 2
        add bx, ax
        mov al, '$'
        mov [bx], al

        pop bp
        ret 2
    input_string ENDP

    output_string PROC
        push bp
        mov bp, sp

        mov ah, 09h
        mov dx, [bp + 4]
        int 21h

        pop bp
        ret 2
    output_string ENDP

    output_number PROC
        push bp
        mov bp, sp  ;[bp + 4] bx
                    ;[bp + 6] number_buffer

        mov ax, [bp + 4]
        mov di, [bp + 6]



        convert_loop:
            xor dx, dx
            div bx

            add dl, 30h
            push dx
            inc cx
            cmp ax, 0
            je final
            jmp convert_loop

        final:
            xor bx, bx

            fill_buffer:

                pop si
                add di, bx
                mov [di], si
                sub di, bx
                inc bx
                loop fill_buffer


            mov ah, 09h
            mov dx, [bp + 6]
            int 21h

            pop bp
            ret 4
    output_number ENDP

    open_file_read PROC
        push bp
        mov bp, sp      ;[bp + 4] file_name

        mov dx, [bp + 4]
        mov ah, 3Dh
        mov al, 00h
        int 21h
        jc missing_file

        pop bp
        ret 2

        missing_file:
            mov ah, 3Eh
            int 21h

            lea dx, message_file_missing
            push dx
            call output_string

            jmp exit
    open_file_read ENDP

    close_file PROC
        push bp
        mov bp, sp  ;[bp + 4] file_descriptor

        mov bx, [bp + 4]
        mov ah, 3Eh
        int 21h

        pop bp
        ret 2
    close_file ENDP    
    
    read_from_file PROC
        push bp
        mov bp, sp

        mov bx, [bp + 4]
        mov cx, file_buffer_size
        lea dx, file_buffer
        mov ah, 3Fh
        int 21h

        pop bp
        ret 2
    read_from_file ENDP

    strlen PROC
        push bp
        mov bp, sp  ;[bp + 4] word

        push si
        push ax

        mov si, [bp + 4]
        mov bx, 0 ;i = 0
        count_length:
            mov al, [si + bx]
            cmp al, '$'
            je return_count
            inc bx
            jmp count_length
        
        return_count:
            pop ax
            pop si
            pop bp
            ret 2
    strlen ENDP

    strcmp PROC
        push bp
        mov bp, sp  ;[bp + 4] str1
                    ;[bp + 6] str2

        push si     ;сохраняем
        push di
        push bx
        push ax
        push cx


        mov si, [bp + 4]
        mov di, [bp + 6]

        push si
        call strlen

        push bx

        push di
        call strlen

        mov ax, bx

        pop bx

        cmp ax, bx
        jne false

        mov bx, 0
        mov cx, ax
        compare:
            ;xor dh, dh
            mov dl, [di]
            mov al, [si]
            cmp dl, al
            jne false

            inc si
            inc di
            inc bx
            cmp bx, cx
            je true
            jmp compare

        true:
            mov dx, 1
            pop cx
            pop ax
            pop bx
            pop di
            pop si

            pop bp
            ret 4

        false:
            mov dx, 0
            pop cx
            pop ax
            pop bx
            pop di
            pop si

            pop bp
            ret 4
    strcmp ENDP

    count_strings PROC
        push bp
        mov bp, sp  ;[bp + 4] file_buffer
                    ;[bp + 6] word_to_find
                    ;[bp + 8] word_buffer

        mov si, [bp + 4]
        mov di, [bp + 6]

        push si
        call strlen

        mov cx, bx  ;strlen
        mov ax, 0   ;i
        mov dx, 0   ;j

        mov bx, [bp + 8]

        main_cycle:
            push ax
            xor ah, ah
            mov al, [si]
            cmp al, ' '
            je next1
            cmp al, 0Dh
            je next1
            cmp al, 0Ah
            je next1
            cmp al, '$'
            je next1

        next2:
            mov al, [si]
            mov [bx], al

            pop ax

            inc ax
            inc si
            inc dx
            inc bx
            cmp ax, cx
            jbe main_cycle

        next1:
            mov al, '$'
            mov [bx], al
            mov bx, [bp + 8]
            mov di, [bp + 6]

            push di
            push bx
            call strcmp

            cmp dx, 01h
            jne skip_inc_counter

            inc counter

            check_loop:
                mov al, 0Dh
                cmp [si], al
                je skip_inc_counter
                mov al, '$'
                cmp [si], al
                je skip_inc_counter

                inc si
                jmp check_loop



            skip_inc_counter:
                mov dx, 0

                mov bx, [bp + 8]
                mov al, '$'
                mov [bx], al

                pop ax

                inc ax
                inc si
                cmp ax, cx
                jbe main_cycle
        pop bp
        ret 6
    count_strings ENDP  

    start:
        mov ax, @data
        mov ds, ax
        
        xor bx, bx
        mov bl, es:[80h] ;CLA length
        add bx, 80h      ;last symbol
        mov si, 82h      ;first symbol
        lea di, file_name

        cmp si, bx
        ja wrong_arguments

        parse_path:
            cmp BYTE PTR es:[si], ' '
            je parsed_path

            mov al, es:[si]
            mov [di], al

            inc di
            inc si
            cmp si, bx
            jbe parse_path

        parsed_path:
            cmp si, bx
            jb wrong_arguments

            lea dx, file_name
            push dx
            call open_file_read     
            mov file_descriptor, ax

            push file_descriptor
            call read_from_file

            push file_descriptor
            call close_file
        
            lea dx, message_input_word
            push dx
            call output_string

            lea dx, word_to_find
            push dx
            call input_string

            lea dx, crlf
            push dx
            call output_string

            lea dx, word_buffer
            push dx
            lea dx, word_to_find
            add dx, 2
            push dx
            lea dx, file_buffer
            push dx
            call count_strings

            lea dx, message_success
            push dx
            call output_string

            lea dx, number_buffer
            push dx
            push counter
            call output_number

            jmp exit
            
        wrong_arguments:
            lea dx, message_arguments_error
            push dx
            call output_string
            jmp exit            

        exit:
            mov ax, 4C00h
            int 21h
    end start