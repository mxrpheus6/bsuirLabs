.8086
.model small
.stack 100h
.data
    string db 200 dup('$')
    word_to_remove db 200 dup('$')
    message1 db 'Enter your string:$'
    message2 db 'Enter word to remove:$'
    crlf db 0Dh, 0Ah, '$'

.code

    input_string PROC
        push bp
        mov bp, sp

        mov ah, 0Ah
        mov dx, [bp + 4]
        int 21h

        mov bx, offset dx
        mov si, [bx + 1]
        add bx, si
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


    ; input:
    ; [bp + 4] -> wordAddr
    ; [bp + 6] -> stringAddr
    ; output: 
    ; ax <- index of word in string        
    find_word PROC
        push bp
        mov bp, sp  ; [bp + 4] -> word
                    ; [bp + 6] -> string

        sub sp, 8   ; [bp - 2] -> strlen
                    ; [bp - 4] -> wordlen
            
                    ; cx -> i
                    ; bx -> j

        mov bx, [bp + 6]
        xor ax, ax
        mov al, [bx + 1] 
        mov [bp - 2], ax  

        mov bx, [bp + 4]
        xor ax, ax
        mov al, [bx + 1] 
        mov [bp - 4], ax

        xor ax, ax
        mov ax, 1
        mov [bp - 6], ax  ;[bp - 6] -> match

        xor ax, ax
        mov ax, [bp - 2]
        sub ax, [bp - 4]
        mov [bp - 8], ax  ; [bp - 8] -> strlen - wordlen         

        xor cx, cx
        find_loop: 

            mov bl, 1
            mov [bp - 6], bl
            xor bx, bx

            check_loop:
                
                mov si, cx
                add si, bx ; si -> i + j
                
                add si, [bp + 6]
                add si, 2 ; si -> i + j + string + 2

                xor ax, ax
                mov al, [si]

                mov si, bx

                add si, [bp + 4]
                add si, 2

                cmp al, [si]
                jne skip

                inc bx
                cmp bx, [bp - 4]
                jb check_loop
            
            mov al, 1
            cmp [bp - 6], al    ;match == 1
            je left_check   ;if match == 1
            ;mov ax, cx

        skip:
            mov al, 0   
            mov [bp - 6], al  ;match = 0
            inc cx
            cmp cx, [bp - 8]
            jbe find_loop 
            jmp done
        
        left_check:
            cmp cx, 0   
            je right_check  ;i == 0
            mov di, [bp + 6]
            add di, 1
            add di, cx  ;str[i-1]

            mov dl, [di]

            mov al, ' '
            cmp dl, al
            je right_check  ;str[i - 1] == 0
            jmp skip
        
        right_check:
            xor ax, ax
            mov ax, cx
            add ax, [bp - 4]    ;i + wordLen
            cmp ax, [bp - 2]    
            je delete_last_word      ;i + wordLen == strlen
            
            mov di, [bp + 6]
            add di, 2
            add di, cx          
            add di, [bp - 4]    ;i + wordLen
            mov dl, [di]
            mov al, ' '
            cmp dl, al  
            mov bx, cx     
            je delete_word      ;str[i + wordLen] == ' '
            jmp skip

        delete_word:
        
            mov si, [bp + 6] 
            add si, 2   
            add si, bx  ;str[j]
            mov di, si
            add di, [bp - 4]    ;str[j + word_len]
            mov al, [di]
            mov [si], al

            inc bx
            cmp bx, [bp - 8]    ;i < strLen - wordLen
            jb delete_word
        
        mov ax, [bp - 4]
        sub [bp - 2], ax
        sub cx, 1
        jmp skip

        delete_last_word :
            mov si, [bp + 6]
            add si, 2
            add si, cx
            mov al, '$'
            mov [si], al
            je done

        done:
            mov di, [bp + 6]  
            add di, 2
            add di, [bp - 2]
            mov al, '$'
            mov [di], al
            mov sp, bp
            pop bp
            ret 4

    find_word ENDP    

    start:
        mov ax, @data
        mov ds, ax

        mov dx, offset message1
        push dx
        call output_string

        mov dx, offset string
        push dx
        call input_string

        mov ah, 09h
        mov dx, offset crlf
        int 21h 

        mov dx, offset message2
        push dx
        call output_string

        mov dx, offset word_to_remove
        push dx
        call input_string 

        mov ah, 09h
        mov dx, offset crlf
        int 21h   

        mov dx, offset string
        push dx
        mov dx, offset word_to_remove
        push dx

        call find_word

        mov dx, offset string
        add dx, 2
        push dx
        call output_string

        mov ax, 4C00h
        int 21h
    end start
