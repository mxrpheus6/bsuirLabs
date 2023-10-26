.8086

.model small

.stack 100h

.data
    message_file_error db "Can't open the file. Try again$"
    file_name db 256 dup('0')
    number_buffer db 9 dup("$")
.code

        output_number PROC
        push bp
        mov bp, sp  ;[bp + 4] bx
                    ;[bp + 6] number_buffer

        mov ax, [bp + 4]
        mov di, [bp + 6]

        test ax, ax
        jns positive
        mov dl, '-'
        mov [di], dl
        inc di

        neg ax

        positive:
            xor bx, bx
            mov bx, 10
            xor cx, cx

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

    start:
        mov ax, @data
        mov ds, ax
        
        xor bx, bx
        mov bl, es:[80h]
        add bx, 80h
        mov si, 82h
        lea di, file_name

        cmp si, bx
        ja bad_arguments

        parse_path:
            cmp BYTE PTR es:[si], ' '
            je parsed_path

            mov al, es:[si]
            mov [dl], al

            inc di
            inc si
            cmp si, bx
            jbe parse_path

        parsed_path:

            ;lea dx, number_buffer
            ;push dx
            ;push bx
            ;call output_number
            
            lea dx, file_name
            mov ah, 09h


        exit:
            mov ax, 4C00h
            int 21h
    end start