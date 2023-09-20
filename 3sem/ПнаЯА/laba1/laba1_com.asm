.model tiny
.code
org 100h

start:
    mov ah, 09h
    mov dx, offset str
    int 21h
        
    int 20h

    str db 'Laba1', 0Dh, 0Ah, 'COM', 0Dh, 0Ah, 'Kazachenko', 0Dh, 0Ah, '$'   
      
end start