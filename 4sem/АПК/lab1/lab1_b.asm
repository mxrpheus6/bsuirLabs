.model small

.stack 100h

.data

result db "Byte recieved: $"

error_write db "Writing error!$"
error_read db  "Reading error!$"
           
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

init_com proc
    push bp
    mov bp, sp ; [bp + 4] com port number

    push ax
    push dx

    xor ax, ax
    mov al, 11100011b
    mov dx, [bp + 4]
    int 14h

    pop dx
    pop ax

    pop bp
    ret 2
init_com endp

write_COM1 proc
    mov ah, 01h
    mov dx, 00h
    mov al, 'B'
    int 14h

    test al, 10000000b
    jz success_write
    
    lea dx, error_write
    push dx
    call output_string
    jmp exit

    success_write:
        ret
write_COM1 endp

read_COM2 proc
    mov ah, 02h
    mov dx, 01h
    int 14h

    ret
read_COM2 endp

start:
    mov ax, @data
    mov ds, ax

    mov dx, 0       
    push dx
    call init_com

    mov dx, 1
    push dx
    call init_com

    call write_COM1

    xor ax, ax
    
    call read_COM2

    lea dx, result
    push dx
    call output_string

    mov ah, 02h
    mov dl, al
    int 21h

    exit: 
        mov ax,4C00h
        int 21h

end start