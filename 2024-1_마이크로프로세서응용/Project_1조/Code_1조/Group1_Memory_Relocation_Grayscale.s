		AREA RESET, DATA, READONLY
		AREA Mem_Reloc_Gray, CODE, READONLY
		; Instead of EXPORT, we add loading function (Function 4) before main function (Grayscale function)
		ENTRY	
		; Initialization

		MOV R1, #0x40000000 ; Starting Address of Input (Image)
		MOV R2, #0x20000000 ; Memory Address of "Storing HEADER"
		MOV R3, #0x30000000 ; Memory Address of "Storing R"
		MOV R4, #0x31000000 ; Memory Address of "Storing G"
		MOV R5, #0x32000000 ; Memory Address of "Storing B"
		; Clear register to use for loading and storing
		MOV R6, #0          
		MOV R7, #0          
		MOV R11, #0 
		B HEADER
		
HEADER_END ; Check "IDAT"
		; We will check 3 bytes before 'T'
		SUB R2, R2, #2
		MOV R10, #0
		LDRB R6, [R2], #-1 ; Check if it is 'A'
		MOV R9, R6
		CMP R9, #0x41
		ADDNE R10, R10, #1 ; If it is not 'A', mark at R10
		LDRB R7, [R2], #-1 ; Check if it is 'D'
		MOV R9, R7
		CMP R9, #0x44
		ADDNE R10, R10, #1 ; If it is not 'D', mark at R10
		LDRB R8, [R2], #-1 ; Check if it is 'I'
		MOV R9, R8
		CMP R9, #0x49
		ADDNE R10, R10, #1 ; If it is not 'I', mark at R10
		; Restore to original state
		STRB R6, [R2, #1]! 
		STRB R7, [R2, #1]!
		STRB R8, [R2, #1]!
		ADD R2, R2, #2
	    CMP R10, #0 ; If R10 != 0, it is not "IDAT"
		MOV R7, #0
		BEQ PIXEL ; If it is "IDAT", terminate loading HEADER and start loading PIXEL
		
HEADER ; Store bytes of HEADER from image
		LDRB R6, [R1]
		STRB R11, [R1], #1
		MOV R7, R6
		STRB R6, [R2], #1
		CMP R7, #0x54 ; Check that current byte is 'T' 
		BNE HEADER ; If it is not 'T', keep loading
		B HEADER_END ; If it is 'T', check if it is 'T' of "IDAT"

PIXEL ; Store bytes of PIXEL from image
		LDRB R6, [R1] ; Store R of RGBA
		STRB R11, [R1], #1
		STRB R6, [R3], #1
		LDRB R6, [R1] ; Store G of RGBA
		STRB R11, [R1], #1
		STRB R6, [R4], #1
		LDRB R6, [R1] ; Store B of RGBA
		STRB R11, [R1], #1
		STRB R6, [R5], #1
		ADD R1, R1, #1 ; Skip A of RGBA
		ADD R7, #4
		CMP R7, #614400 ; 614400 = 960 * 160 * 4 (Bytes)
		BNE PIXEL

		; Here is starting point of Function 1, Convert to RGB

        MOV R1, #0x30000000 ; Memory address of R
        MOV R2, #0x31000000 ; Memory address of G
		MOV R3, #0x32000000 ; Memory address of B
		MOV R4, #0x25000000 ; Memory address of Grayscale
		MOV R11, #0x31000000 ; End address of R
		MOV R5, #0
		
Grayscale
		LDRB  R6, [R1], #1 ; Load Red value
		LDRB  R7, [R2], #1 ; Load Green value
		LDRB  R8, [R3], #1 ; Load Blue value
		ADD   R5, R6, R7   ; R5 = R + G + B
		ADD   R5, R5, R8
		; We will divide by 3 using subtraction loop
		MOV   R9, #0       ; Initialize result of division
		MOV   R10, #3      ; Divisor = 3

Divide_by_3
		CMP   R5, R10      ; Check if R5 >= R10
		SUBCS R5, R5, R10  ; R5 -= R10 (Sbtraction if carry set)
		ADDCS R9, R9, #1   ; R9 += 1 (Increment result if carry set)
		BCS   Divide_by_3  ; Loop back if carry set

		STRB  R9, [R4], #1 ; Store the grayscale value

		CMP   R1, R11      ; Check if it is end of PIXEL data
		BLT   Grayscale    ; If it is not end, continue

		END