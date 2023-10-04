.8086
.model small
.stack 100h

.data
    message1 db "Enter size of array:$"
    message2 db "Enter element of array:$"
    sign db "+"
    overflow_message db "Overflow detected!$"
    not_digit_message db "There are not digits in your input$"
    correction_message db "Enter correct number:$"
    result_message db "The most popular number in array is $"
    input_string_buffer db 200 dup ("$")
    number_buffer db 9 dup("$")
    crlf db 0Dh, 0Ah, '$'
    arr dw 200 dup(?)
    size dw ?

.code

    output_string PROC
        push bp
        mov bp, sp

        mov ah, 09h
        mov dx, [bp + 4]
        int 21h

        pop bp
        ret 2
    output_string ENDP

    input_number PROC
        push bp
        mov bp, sp  ;[bp + 4] input_string_buffer

        input:
            mov ah, 0Ah
            mov dx, [bp + 4]
            int 21h

            xor ax, ax          ;res
            mov si, [bp + 4]    ;input_string_buffer
            mov cl, [si + 1]    ;length
            add si, 2
            mov bl, [si]
            cmp bl, '-'
            je set_negative_sign

            parse_loop:
                xor bx, bx
                mov bl, [si]
                sub bl, 48
                cmp bl, 0
                jb handle_not_digit
                cmp bl, 9
                ja handle_not_digit
                push bx
                mov bx, 10
                imul bx
                pop bx
                jo handle_overflow  ;amount of nums is big
                xor bh, bh
                add ax, bx
                jo handle_overflow  ;after big number 
                inc si
                loop parse_loop

                lea di, sign
                mov dl, '-'
                cmp [di], dl
                je set_negative
                jmp exit

            handle_not_digit:
                mov ah, 09h
                lea dx, crlf
                int 21h
                mov ah, 09h
                mov dx, offset not_digit_message
                int 21h
                jmp reload
                
            handle_overflow:
                mov ah, 09h
                lea dx, crlf
                int 21h
                mov ah, 09h
                lea dx, overflow_message
                int 21h
                jmp reload

            set_negative_sign:
                lea di, sign
                mov bl, '-' 
                mov [di], bl
                inc si
                dec cl
                jmp parse_loop

            reload:
                mov bl, '+'
                lea di, sign
                mov [di], bl

                xor ax, ax
                xor bx, bx
                xor cx, cx
                xor dx, dx
                xor di, di
                xor si, si
                
                mov ah, 09h
                lea dx, crlf
                int 21h

                mov ah, 09h
                lea dx, correction_message
                int 21h

                jmp input
            

            set_negative:
                neg ax
            
            exit:
                mov bl, '+'
                lea di, sign
                mov [di], bl

                pop bp
                ret 2

    input_number ENDP


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

    fill_array PROC
        push bp
        mov bp, sp  ;[bp + 4] array
                    ;[bp + 6] input_string_buffer
                    ;[bp + 8] size
        
        xor cx, cx
        xor si, si
        xor bx, bx

        fill_loop:
            lea dx, message2
            push dx
            call output_string

            push bx
            push cx
            push [bp + 6]
            call input_number
            mov dx, ax
            pop cx
            pop bx

            push dx
            lea dx, crlf
            push dx
            call output_string
            pop dx

            mov di, [bp + 4]
            mov [bx + di], dx
            add bx, 2 
            inc cx
            mov si, [bp + 8]
            cmp cx, [si]
            jb fill_loop

        pop bp
        ret 6
    fill_array ENDP

    find_popular PROC
        push bp
        mov bp, sp  ;[bp + 4] arr
                    ;[bp + 6] size
        
        sub sp, 2   ;[bp - 2] temp

        xor bx, bx
        mov si, [bp + 6]
        mov ax, [si]
        mov bl, 2
        imul bx
        sub ax, 2
        mov [si], ax    ;size * 2

        mov di, [bp + 4];arr
        mov ax, [di]    ;max
        xor cx, cx      ;maxCounter
        mov cl, 1
        
        xor bx, bx
        mov bl, 2   ;i

        first_elem:
            cmp [di+bx], ax 
            jne skip_inc    ;arr[i] != max
            inc cx          ;maxCounter++

            skip_inc:   
            cmp bx, [si]    ;i < length
            je other_elements  
            add bx, 2       ;i++ 
            jmp first_elem

        other_elements:
            xor bx, bx
            mov bl, 2   ;i

        check:
            cmp [di + bx], ax
            je skip

            xor dx, dx ; j
            mov [bp - 2], 0
        cycl:
            push si
            mov si, di
            add si, dx
            push dx
            mov dx, [si]
            cmp [bx + di], dx
            pop dx
            pop si
            je operations

            cmp dx, [si]
            je last_check
            add dx, 2
            jmp cycl

        operations:
            add [bp - 2], 1 ;temp++ 
            cmp dx, [si]
            je last_check
            add dx, 2
            jmp cycl

        last_check:
            cmp [bp - 2], cx
            ja swap

        skip:
            cmp bx, [si]
            je done
            add bx, 2
            jmp check

        swap:
            mov cx, [bp - 2]
            mov ax, [bx + di]
            jmp skip
        
        done:
            mov sp, bp
            pop bp
            ret 4
    find_popular ENDP
    
    start:
        mov ax, @data
        mov ds, ax

        lea dx, message1
        push dx
        call output_string

        lea dx, input_string_buffer
        push dx
        call input_number

        mov [size], ax

        lea dx, crlf
        push dx
        call output_string
        
        push offset size
        push offset input_string_buffer
        push offset arr
        call fill_array



        push offset size
        push offset arr
        call find_popular

        push ax

        lea dx, result_message
        push dx
        call output_string

        pop ax

        lea dx, number_buffer
        push dx
        push ax
        call output_number

        mov ax, 4C00h
        int 21h
    end start 
