.model flat, c

.code

func PROC
	push ebp
	mov ebp, esp

	arr	equ [ebp + 8]
	res	equ [ebp + 12]

	mov esi, arr
	mov edi, res

	mov ebx, 4	;i = 1

	finit
	
	fld dword ptr [esi]
	fstp dword ptr [edi]

	main_cycle:
		cmp ebx, 40
		jae exit

		fld dword ptr [edi + ebx - 4]
		fadd dword ptr [esi + ebx]
		fstp dword ptr [edi + ebx]

		add ebx, 4
		jmp main_cycle

		exit:
			pop ebp
			ret
func ENDP

end