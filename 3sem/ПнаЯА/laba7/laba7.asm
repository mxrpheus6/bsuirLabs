.186

.model small

.stack 256

.data
    message_arguments_error        db "Wrong arguments. Try: 'laba7 directory_name'.$"
    message_catalog_missing        db "Can't find catalog. Probably it's missing.$"
    message_running_error          db "Can't run exe.$"
    
    command_line                   db 128

    command_line_text              db 128 dup(0)

    file_name                      db "*.exe", 0

    DTA_size    equ 2Ch
    DTA_block   db DTA_size dup(0)

    EBP_block dw 0
              dw offset command_line, 0
              dw 005Ch, 0, 006Ch, 0

    data_segment_size = $ - message_arguments_error

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

    change_directory PROC
        push bp
        mov bp, sp  ;[bp + 4] command_line_text

        mov ah, 3Bh
        lea dx, command_line_text
        int 21h
        jc missing_catalog

        pop bp
        ret 2

        missing_catalog:
            lea dx, message_catalog_missing 
            push dx
            call output_string
            jmp exit
    change_directory ENDP     

    initialize_dta PROC
        mov ah, 1Ah
        lea dx, DTA_block
        int 21h
        ret
    initialize_dta ENDP      

    find_first_file PROC
        call initialize_dta

        xor cx, cx
        mov ah, 4Eh
        lea dx, file_name
        int 21h

        jc missing_first_file
        
        mov ax, 0

        jmp first_found

        missing_first_file:
            mov ax, 1

        first_found:
            ret
    find_first_file ENDP     

    find_next_file PROC
        call initialize_dta

        xor cx, cx
        mov ah, 4Fh
        lea dx, file_name
        int 21h

        jc missing_next_file
        
        mov ax, 0

        jmp next_found

        missing_next_file:
            mov ax, 1

        next_found:
            ret
    find_next_file ENDP   

    run_exe PROC
        push bx
        push dx

        mov ax, 4B00h
        lea bx, EBP_block
        mov dx, offset DTA_block + 1Eh
        int 21h

        jc runing_exe_error

        mov ax, 0

        jmp success_run

        runing_exe_error:
            lea dx, message_running_error
            push dx
            call output_string
            mov ax, 1

        success_run:
            pop dx
            pop bx
            ret
    run_exe ENDP     

    start:
        mov ah, 4Ah
        mov bx, ((code_segment_size / 16) + 1) + ((data_segment_size / 16) + 1) + 16 + 16
        int 21h
        jc exit
    
        mov ax, @data
        mov ds, ax
        
        xor bx, bx
        mov bl, es:[80h] ;CLA length
        add bx, 80h      ;last symbol
        mov si, 82h      ;first symbol
        lea di, command_line_text 

        cmp si, bx
        ja wrong_arguments

        parse_catalog:
            cmp BYTE PTR es:[si], ' '
            je parsed_catalog

            mov al, es:[si]
            mov [di], al

            inc di
            inc si
            cmp si, bx
            jbe parse_catalog

        parsed_catalog:
            cmp si, bx
            jb wrong_arguments

            lea dx, command_line_text
            push dx
            call change_directory

            call find_first_file
            cmp ax, 0
            jne exit

            call run_exe
            cmp ax, 0
            jne exit

            run_other_files:
                call find_next_file
                cmp ax, 0
                jne exit

                call run_exe
                cmp ax, 0
                jne exit

                jmp run_other_files
    
        wrong_arguments:
            lea dx, message_arguments_error
            push dx
            call output_string
            jmp exit
        
    exit:
        mov ax, 4C00h
        int 21h

        code_segment_size = $ - output_string

    end start