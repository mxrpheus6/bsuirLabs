.8086
.model small
.stack 100h

.data

    ;units
    pac_man         equ 02h
    ghost           equ 40h
    coin            equ 03h

    yellow_color    equ 0Eh
    green_color     equ 0Ah
    red_color       equ 04h

    ;score
    score       dw 0
    info_line   db 'S', 3Fh, 'c', 3Fh,'o', 3Fh, 'r', 3Fh, 'e', 3Fh, ':', 3Fh, ' ', 3Fh, '0', 3Fh, 32 dup (' ', 3Fh)
    score_for_operations            dw 0
    one_digit_of_score              dw 0
    digits_of_score                 dw 0
    ten                             db 10

    ;random
    random_number       dw 0
    lcg_mul_const       equ 25173
    lcg_inc_const       equ 13849

    ;map
    position    dw 0
    wall        db ' ', 5Fh
    red_wall    db ' ', 47h
    black_space     db ' ', 00h
    map_width   equ 40
    map_height  equ 25
    
map db 40 dup ('w')
    db 'w', 4 dup('s'), 2 dup('w'), 12 dup('s'), 2 dup('w'), 12 dup('s'), 2 dup('w'), 4 dup('s'), 'w'
    db 'w', 's', 2 dup('w'), 's', 2 dup('w'), 's', 4 dup('w'), 's', 5 dup('w'), 's', 2 dup('w'), 's', 5 dup('w'), 's', 4 dup('w'), 's', 2 dup('w'), 's', 2 dup('w'), 's', 'w'
    db 'w', 's', 2 dup('w'), 's', 2 dup('w'), 's', 4 dup('w'), 3 dup('s'), 'w', 8 dup('s'), 'w', 3 dup('s'), 4 dup('w'), 's', 2 dup('w'), 's', 2 dup('w'), 's', 'w'
    db 'w', 12 dup('s'), 'w', 's', 'w', 's', 6 dup('w'), 's', 'w', 's', 'w', 12 dup('s'), 'w'
    db 4 dup('w'), 's', 5 dup('w'), 's', 3 dup('w'), 's', 'w', 's', 6 dup('w'), 's', 'w', 's', 3 dup('w'), 's', 5 dup('w'), 's', 4 dup('w')
    db 4 dup('w'), 's', 'w', 5 dup('s'), 'w', 16 dup('s'), 'w', 5 dup('s'), 'w', 's', 4 dup('w')
    db 'w', 4 dup('s'), 'w', 's', 3 dup('w'), 3 dup('s'), 'w', 's', 10 dup('w'), 's', 'w', 3 dup('s'), 3 dup('w'), 's', 'w', 4 dup('s'), 'w'
    db 'w', 's', 2 dup('w'), 's', 'w', 's', 3 dup('w'), 's', 'w', 's', 'w', 's', 10 dup('w'), 's', 'w', 's', 'w', 's', 3 dup('w'), 's', 'w', 's', 2 dup('w'), 's', 'w'
    db 'w', 's', 2 dup('w'), 's', 'w', 's', 2 dup('w'), 2 dup('s'), 'w', 's', 'w', 12 dup('s'), 'w', 's', 'w', 2 dup('s'), 2 dup('w'), 's', 'w', 's', 2 dup('w'), 's', 'w'
    db 'w', 9 dup('s'), 2 dup('w'), 's', 'w', 's', 10 dup('w'), 's', 'w', 's', 2 dup('w'), 9 dup('s'), 'w'
    db 'w','s', 2 dup('w'), 's', 4 dup('w'), 's', 2 dup('w'), 's', 'w', 's', 10 dup('w'), 's', 'w', 's', 2 dup('w'), 's', 4 dup('w'), 's', 2 dup('w'), 's', 'w'
    db 'w','s', 2 dup('w'), 's', 4 dup('w'), 's', 2 dup('w'), 3 dup('s'), 10 dup('w'), 3 dup('s'), 2 dup('w'), 's', 4 dup('w'), 's', 2 dup('w'), 's', 'w'
    db 'w', 10 dup('s'), 'w', 's', 'w', 's', 10 dup('w'), 's', 'w', 's', 'w', 10 dup('s'), 'w'
    db 'w', 's', 2 dup('w'), 's', 'w', 's', 'w', 's', 'w', 's', 'w', 's', 'w', 12 dup('s'), 'w', 's', 'w', 's', 'w', 's', 'w', 's', 'w', 's', 2 dup('w'), 's', 'w'
    db 'w', 's', 2 dup('w'), 's', 'w', 's', 'w', 5 dup('s'), 'w', 's', 10 dup('w'), 's', 'w', 5 dup('s'), 'w', 's', 'w', 's', 2 dup('w'), 's', 'w' 
    db 'w', 4 dup('s'), 'w', 's', 2 dup('w'), 's', 4 dup('w'), 's', 10 dup('w'), 's', 4 dup('w'), 's', 2 dup('w'), 's', 'w', 4 dup('s'), 'w'
    db 4 dup('w'), 's', 'w', 28 dup('s'), 'w', 's', 4 dup('w')
    db 4 dup('w'), 's', 5 dup('w'), 's', 3 dup('w'), 's', 'w', 's', 6 dup('w'), 's', 'w', 's', 3 dup('w'), 's', 5 dup('w'), 's', 4 dup('w')
    db 'w', 10 dup('s'), 3 dup('w'), 's', 'w', 's', 6 dup('w'), 's', 'w', 's', 3 dup('w'), 10 dup('s'), 'w'
    db 'w', 's', 2 dup('w'), 's', 2 dup('w'), 's', 2 dup('w'), 5 dup('s'), 'w', 8 dup('s'), 'w', 5 dup('s'), 2 dup('w'), 's', 2 dup('w'), 's', 2 dup('w'), 's', 'w'
    db 'w', 's', 2 dup('w'), 's', 2 dup('w'), 's', 2 dup('w'), 's', 'w', 's', 5 dup('w'), 's', 2 dup('w'), 's', 5 dup('w'), 's', 'w', 's', 2 dup('w'), 's', 2 dup('w'), 's', 2 dup('w'), 's', 'w'
    db 'w', 4 dup('s'), 2 dup('w'), 4 dup('s'), 'w', 16 dup('s'), 'w', 4 dup('s'), 2 dup('w'), 4 dup('s'), 'w'
    db 40 dup ('w')

    ;death screen
death_screen db 80 dup('w')
             db 280 dup('s')
             db 3 dup('s'), 'w', 5 dup('s'),  'w', 's', 3 dup('w'), 's', 'w', 's', 'w', 2 dup('s'), 'w', 3 dup('s'), 3 dup('w'), 's', 3 dup('w'), 's', 3 dup('w'), 5 dup('s')
             db 4 dup('s'), 'w', 3 dup('s'), 'w', 2 dup('s'), 'w', 's', 'w', 's', 'w', 's', 'w', 2 dup('s'), 'w', 3 dup('s'), 'w', 's', 'w', 's', 3 dup('w'), 's', 3 dup('w'), 5 dup('s')
             db 5 dup('s'), 'w', 's', 'w', 3 dup('s'), 'w', 's', 'w', 's', 'w', 's', 'w', 2 dup('s'), 'w', 3 dup('s'), 'w', 's', 'w', 's', 2 dup('w'), 2 dup('s'), 'w', 7 dup('s')
             db 6 dup('s'), 'w', 4 dup('s'), 'w', 's', 'w', 's', 'w', 's', 'w', 2 dup('s'), 'w', 3 dup('s'), 'w', 's', 'w', 's', 2 dup('w'), 2 dup('s'), 3 dup('w'), 5 dup('s')
             db 6 dup('s'), 'w', 4 dup('s'), 'w', 's', 'w', 's', 'w', 's', 'w', 2 dup('s'), 'w', 3 dup('s'), 'w', 's', 'w', 2 dup('s'), 2 dup('w'), 's', 3 dup('w'), 5 dup('s')
             db 6 dup('s'), 'w', 4 dup('s'), 'w', 's', 'w', 's', 'w', 's', 'w', 2 dup('s'), 'w', 3 dup('s'), 'w', 's', 'w', 2 dup('s'), 2 dup('w'), 's', 'w', 7 dup('s')
             db 6 dup('s'), 'w', 4 dup('s'), 'w', 's', 'w', 's', 'w', 's', 'w', 2 dup('s'), 'w', 3 dup('s'), 'w', 's', 'w', 's', 3 dup('w'), 's', 3 dup('w'), 5 dup('s')
             db 6 dup('s'), 'w', 4 dup('s'), 3 dup('w'), 's', 3 dup('w'), 2 dup('s'), 3 dup('w'), 's', 3 dup('w'), 's', 3 dup('w'), 's', 3 dup('w'), 5 dup('s')
             db 200 dup('s')
             db 80 dup('w')

    ;player
    player_skin         db pac_man, yellow_color
    player_direction    db ?
    player_position     dw 881

    ;ghosts
    ghost_skin              db ghost, green_color
    first_ghost_position    dw 187
    second_ghost_position   dw 246
    third_ghost_position    dw 823

    ;coin
    coin_skin  db coin, red_color
    coin_position dw 764  

.code

    set_field PROC
        mov bx, 0
        mov cx, 25
        setting_rows_map:
            push cx

            mov cx, map_width
            mov di, position
            add di, di
            setting_cols_map:
                cmp map[bx], 'w'
                jne skip1_map
                lea si, wall
                movsw
                jmp skip2_map
                skip1_map:
                    add si, 2
                    add di, 2
                skip2_map:
                    inc position
                    inc bx
                    loop setting_cols_map
                    pop cx 
                    loop setting_rows_map
            
        mov position, 0
        ret
    set_field ENDP
    
    set_death_screen proc
        mov bx, 0   ;i
        mov cx, 25
        setting_rows_screen:
            push cx

            mov cx, map_width
            mov di, position
            add di, di
            setting_cols_screen:
                cmp death_screen[bx], 'w'
                jne skip1_screen
                lea si, red_wall
                movsw
                jmp skip2_screen
                skip1_screen:
                    lea si, black_space
                    movsw
                skip2_screen:
                    inc position
                    inc bx
                    loop setting_cols_screen
                    pop cx 
                    loop setting_rows_screen
            
        mov position, 0
        ret
    set_death_screen endp

    set_field_info PROC
        push cx

        mov cx, map_width
        add cx, cx
        lea si, info_line
        mov di, 1920
        rep movsb

        pop cx
        ret
    set_field_info ENDP

    set_player_and_ghosts PROC
        lea si, player_skin
        mov di, player_position
        add di, di
        movsw

        lea si, ghost_skin
        mov di, first_ghost_position
        add di, di
        movsw

        lea si, ghost_skin
        mov di, second_ghost_position
        add di, di
        movsw

        lea si, ghost_skin
        mov di, third_ghost_position
        add di, di
        movsw

        ret
    set_player_and_ghosts ENDP

    set_coin PROC
        lea si, coin_skin
        mov di, coin_position
        add di, di
        movsw

        ret
    set_coin ENDP

    clear_player_position PROC
        lea si, black_space
        mov di, player_position
        add di, di
        movsb

        ret
    clear_player_position ENDP

    clear_ghost_position PROC
        lea si, black_space
        mov di, bx
        add di, di
        movsb

        ret
    clear_ghost_position ENDP

    inc_score PROC
        inc score
        ret
    inc_score ENDP

    set_score proc

        push cx

        mov bx, score
        mov score_for_operations, bx
        mov digits_of_score, 0

        mov ax, score_for_operations
        mul ten
        mov score_for_operations, ax

        setting_digits_of_score:

        inc digits_of_score

        mov ax, score_for_operations
        div ten
        xor ah,ah
        mov score_for_operations, ax

        cmp score_for_operations, 10
        jae setting_digits_of_score

        mov di,1932
        add di, digits_of_score
        add di, digits_of_score

        mov ax, score
        mov score_for_operations, ax

        writing_score:

            mov ax, score_for_operations
            div ten

            mov bx, ax
            xor bh, bh
            mov score_for_operations, bx
            mov al, ah
            xor ah, ah
            mov one_digit_of_score, ax
            add one_digit_of_score, 48
            dec digits_of_score
            mov si, offset one_digit_of_score
            movsb
            sub di, 3

            cmp digits_of_score, 0
            jne writing_score
            pop cx
            ret
    set_score endp

    random PROC
        mov ax, lcg_mul_const
        mul random_number
        add ax, lcg_inc_const

        mov random_number, ax
        xor dx, dx
        mov cx, 1000
        div cx

        ret
    random ENDP

    generate_coin PROC

        generating:
            ;mov cx, 0
            mov coin_position, 0

            call random
            cmp dx, 919
            jae generating
            mov coin_position, dx
            
            mov bx, coin_position
            cmp map[bx], 'w'
            je generating
            
            ret
    generate_coin ENDP

    ghosts_movements PROC
        moving_first_ghost:
            mov bx, first_ghost_position
            call clear_ghost_position
            call random
            cmp dx, 750
            jae try_up_first
            cmp dx, 500
            jae try_down_first
            cmp dx, 250
            jae try_right_first
            sub bx, 1
            cmp map[bx], 'w'
            je moving_first_ghost
            jmp moved_first
            try_up_first:
                sub bx, 40
                cmp map[bx], 'w'
                je moving_first_ghost
                jmp moved_first
            try_down_first:
                add bx, 40
                cmp map[bx], 'w'
                je moving_first_ghost
                jmp moved_first
            try_right_first:
                add bx, 1
                cmp map[bx], 'w'
                je moving_first_ghost
                jmp moved_first
            moved_first:
                mov first_ghost_position, bx

        moving_second_ghost:
            mov bx, second_ghost_position
            call clear_ghost_position
            call random
            cmp dx, 750
            jae try_up_second
            cmp dx, 500
            jae try_down_second
            cmp dx, 250
            jae try_right_second
            sub bx, 1
            cmp map[bx], 'w'
            je moving_second_ghost
            jmp moved_second
            try_up_second:
                sub bx, 40
                cmp map[bx], 'w'
                je moving_second_ghost
                jmp moved_second
            try_down_second:
                add bx, 40
                cmp map[bx], 'w'
                je moving_second_ghost
                jmp moved_second
            try_right_second:
                add bx, 1
                cmp map[bx], 'w'
                je moving_second_ghost
                jmp moved_second
            moved_second:
                mov second_ghost_position, bx

        moving_third_ghost:
            mov bx, third_ghost_position
            call clear_ghost_position
            call random
            cmp dx, 750
            jae try_up_third
            cmp dx, 500
            jae try_down_third
            cmp dx, 250
            jae try_right_third
            sub bx, 1
            cmp map[bx], 'w'
            je moving_third_ghost
            jmp moved_third
            try_up_third:
                sub bx, 40
                cmp map[bx], 'w'
                je moving_third_ghost
                jmp moved_third
            try_down_third:
                add bx, 40
                cmp map[bx], 'w'
                je moving_third_ghost
                jmp moved_third
            try_right_third:
                add bx, 1
                cmp map[bx], 'w'
                je moving_third_ghost
                jmp moved_third
            moved_third:
                mov third_ghost_position, bx

        ret
    ghosts_movements ENDP   

    check PROC
            mov dx, first_ghost_position
            cmp player_position, dx
            je death

            mov dx, second_ghost_position
            cmp player_position, dx
            je death

            mov dx, third_ghost_position
            cmp player_position, dx
            je death

            ret

            death:
                call set_death_screen

                mov ax, 4C00h
                int 21h
    check ENDP

    start:
        mov ax, @data
        mov ds, ax

        mov ah, 00h
        mov al, 01h
        int 10h

        mov ah, 01h
        mov cx, 2607h
        int 10h

        mov ax, 0B800h
        mov es, ax

        call set_field
        call set_field_info
        call set_player_and_ghosts
        call set_coin

        main_cycle:
            mov cx, 0

            mov ah, 86h
            mov dx, 65535
            int 15h
            int 15h
            int 15h

            call check

            mov dx, coin_position
            cmp player_position, dx
            jne skip_coin_operations
            call inc_score
            call generate_coin
            call set_coin
            call set_score
            skip_coin_operations:

                call ghosts_movements
                call set_player_and_ghosts
                
                mov ah, 01h
                int 16h
                jz no_key

                mov ah, 00h
                int 16h

                cmp ah, 11h
                jne not_w
                mov player_direction, 'w'
                jmp no_key

                not_w:
                    cmp ah, 1Fh
                    jne not_s
                    mov player_direction, 's'
                    jmp no_key
                not_s:
                    cmp ah, 1Eh
                    jne not_a
                    mov player_direction, 'a'
                    jmp no_key
                not_a:
                    cmp ah, 20h
                    jne not_d
                    mov player_direction, 'd'
                    jmp no_key
                not_d:

                no_key:
                    cmp player_direction, 'w'
                    je is_w
                    cmp player_direction, 's'
                    je is_s
                    cmp player_direction, 'a'
                    je is_a
                    cmp player_direction, 'd'
                    je is_d

                jmp main_cycle

                is_w:
                    mov si, player_position
                    sub si, 40
                    cmp map[si], 'w'
                    je wall_
                    call clear_player_position
                    sub player_position, 40
                    call check
                    jmp wall_
                is_s:
                    mov si, player_position
                    add si, 40
                    cmp map[si], 'w'
                    je wall_
                    call clear_player_position
                    add player_position, 40
                    jmp wall_
                is_a:
                    mov si, player_position
                    sub si, 1
                    cmp map[si], 'w'
                    je wall_
                    call clear_player_position
                    sub player_position, 1
                    jmp wall_
                is_d:
                    mov si, player_position
                    add si, 1
                    cmp map[si], 'w'
                    je wall_
                    call clear_player_position
                    add player_position, 1
                    jmp wall_


                    wall_:
                        call set_player_and_ghosts
                        jmp main_cycle

        mov ax, 4C00h
        int 21h
    end start