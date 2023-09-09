.model small
.stack 100h
.code
start:
    mov ax, @data
    mov ds, ax
    mov dx, offset str
    mov ah, 09h
    int 21h
    mov ax, 4C00h
    int 21h   
    
.data
    str db 'Laba1', 0Dh, 0Ah, 'EXE', 0Dh, 0Ah, 'Kazachenko', 0Dh, 0Ah, '$'   
end start