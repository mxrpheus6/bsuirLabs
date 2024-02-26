.model small

.stack 100h

.data

result db "Byte recieved: $"

error_write db "Writing error!$"
error_read db  "Reading error!$"
           
data_write db 'C'
data_read db ?

.code

output_string proc
    push bp
    mov bp, sp ;[bp + 4] string

    push ax
    push dx

    mov ah, 09h
    mov dx, offset [bp + 4]
    int 21h

    pop dx
    pop ax

    pop bp
    ret 2
output_string endp

init_COM1 proc
    push ax
    push dx

    mov dx, 3FBh
    mov al, 80h
    out dx, al

    mov dx, 3F8h
    mov al, 00h
    out dx, al
    mov dx, 3F9h
    mov al, 0Ch
    out dx, al

    mov dx, 3FCh
    mov al, 00001011b
    out dx, al

    mov dx, 3F9h
    mov al, 00h
    out dx, al

    pop dx
    pop ax
    ret 
init_COM1 endp

init_COM2 proc
    push ax
    push dx

    mov dx, 2FBh
    mov al, 80h
    out dx, al

    mov dx, 2F8h
    mov al, 00h
    out dx, al
    mov dx, 2F9h
    mov al, 0Ch
    out dx, al

    mov dx, 2FCh
    mov al, 00001011b
    out dx, al

    mov dx, 2F9h
    mov al, 00h
    out dx, al

    pop dx
    pop ax
    ret 
init_COM2 endp

write proc
    push ax
    push dx

    xor al, al
    mov dx, 3FDh
    in al, dx
    test al, 10h
    jz success_write
    
    lea dx, error_write
    push dx
    call output_string
    jmp exit

    success_write:
        mov dx, 3F8h
        mov al, data_write
        out dx, al

        pop dx
        pop ax
        ret
write endp

read proc
    push ax
    push dx

    xor al,al
    mov dx,3FDh
    in al,dx
    test al,10b
    jz success_read
    
    lea dx, error_read
    push dx
    call output_string
    jmp exit

    success_read:
        mov dx, 3F8h
        in al, dx
        mov data_read, al

        pop dx
        pop ax
        ret
read endp

start:
    mov ax, @data
    mov ds, ax

    call init_COM1
    call init_COM2

    call write
    call read

    mov ah, 02h
    mov dl, data_read
    int 21h

    exit:
        mov ax, 4C00h
        int 21h
end start