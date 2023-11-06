.model tiny               
.code        
              
	org 100h    
    start:

        jmp main

        message_arguments_error        db "Wrong arguments. Try: 'laba8.com stopHour stopMin stopSec signalDurationHour signalDurationMin signalDurationSec$"
        
        alarm_status                   db 0     ;0 - выкл, 1 - вкл

        stopHour            db 0 
        stopMin             db 0
        stopSec             db 0

        signalDurationHour  db 0
        signalDurationMin   db 0
        signalDurationSec   db 0

        finalHour          db 0
        finalMin           db 0
        finalSec           db 0

        ;баннер
        widthOfBanner       equ 40
        allWidth            equ 80
        yellow              equ 6020h
        white               equ 7020h
        black               equ 0020h

        wakeUpText 	dw 2 * widthOfBanner dup(yellow)
                    dw 6 dup(yellow), 3 dup(white), 2 dup(yellow), white, 6 dup(yellow), 3 dup(white), 2 dup(yellow), 5 dup(white), 2 dup(yellow), white, 3 dup(yellow), white, 5 dup(yellow)
                    dw 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 4 dup(yellow), white, yellow, 2 dup(white), yellow, 2 dup(white), 5 dup(yellow)
                    dw 5 dup(yellow), 5 dup(white), yellow, white, 5 dup(yellow), 5 dup(white), yellow, 5 dup(white), 2 dup(yellow), white, yellow, white, yellow, white, 5 dup(yellow)
                    dw 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 2 dup(yellow), white, 3 dup(yellow), white, 3 dup(yellow), white, 5 dup(yellow)
                    dw 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 5 dup(yellow), white, 3 dup(yellow), white, yellow, white, 3 dup(yellow), white, 2 dup(yellow), white, 3 dup(yellow), white, 5 dup(yellow)
                    dw 5 dup(yellow), white, 3 dup(yellow), white, yellow, 5 dup(white), yellow, white, 3 dup(yellow), white, yellow, white, 4 dup(yellow), white, yellow, white, 3 dup(yellow), white, 5 dup(yellow)
			        dw 2 * widthOfBanner dup(yellow)

        offWakeUp	dw widthOfBanner dup(black)
			        dw widthOfBanner dup(black)
			        dw widthOfBanner dup(black)
			        dw widthOfBanner dup(black)
			        dw widthOfBanner dup(black) 
			        dw widthOfBanner dup(black)
			        dw widthOfBanner dup(black)
                    dw widthOfBanner dup(black)
                    dw widthOfBanner dup(black)
                    dw widthOfBanner dup(black)    

        printBanner PROC                      
            push es

            push ax
            mov ax, 0B800h                          
            mov es, ax
            pop ax                      
                                           
            mov di, 9 * allWidth * 2 + (allWidth - widthOfBanner) 
            mov cx, 10                         
        loopPrintBanner:                     
            push cx
                                            
            mov cx, widthOfBanner
            rep movsw                         
                                         
            add di, 2 * (allWidth - widthOfBanner)
                                          
            pop cx                          
            loop loopPrintBanner             
            pop es                          
            ret                               
        printBanner ENDP  
        
        main:

            lea si, wakeUpText
            call printBanner
        
        ret

    end start