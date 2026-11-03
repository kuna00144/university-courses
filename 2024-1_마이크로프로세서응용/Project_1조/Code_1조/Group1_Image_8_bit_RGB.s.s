		AREA RESET, DATA, READONLY
		AREA Image_RGB, CODE, READONLY

		ENTRY	
		; Initialization
		MOV R1, #0x40000000 ; Starting Address of Input (Image)
		MOV R2, #0x20000000 ; Memory Address of "Storing HEADER"
		MOV R3, #0x30000000 ; Memory Address of "Storing PIXEL"
		; Clear register to use for loading and storing
		MOV R4, #0          
		MOV R5, #0          
		MOV R10, #0 
		B HEADER
		
HEADER_END ; Check "IDAT"
		; We will check 3 bytes before 'T'
		SUB R2, R2, #2
		MOV R7, #0
		LDRB R4, [R2], #-1 ; Check if it is 'A'
		MOV R6, R4
		CMP R6, #0x41
		ADDNE R7, R7, #1 ; If it is not 'A', mark at R7
		LDRB R4, [R2], #-1 ; Check if it is 'D'
		MOV R5, R4
		CMP R5, #0x44
		ADDNE R7, R7, #1 ; If it is not 'D', mark at R7
		LDRB R4, [R2], #-1 ; Check if it is 'I'
		CMP R4, #0x49
		ADDNE R7, R7, #1 ; If it is not 'I', mark at R7
		; Restore to original state
		STRB R4, [R2, #1]! 
		STRB R5, [R2, #1]!
		STRB R6, [R2, #1]!
		ADD R2, R2, #2
	    CMP R7, #0 ; If R7 != 0, it is not "IDAT"
		MOV R5, #0 ; Reset R5 to use
		BEQ PIXEL ; If it is "IDAT", terminate loading HEADER and start loading PIXEL
		
HEADER ; Store bytes of HEADER from image
		LDRB R4, [R1]
		STRB R10, [R1], #1
		MOV R5, R4
		STRB R4, [R2], #1
		CMP R5, #0x54 ; Check that current byte is 'T' 
		BNE HEADER ; If it is not 'T', keep loading
		B HEADER_END ; If it is 'T', check if it is 'T' of "IDAT"

PIXEL ; Store bytes of PIXEL from image
		LDRB R4, [R1]
		STRB R10, [R1], #1
		STRB R4, [R3], #1
		ADD R5, #1
		CMP R5, #614400 ; 614400 = 960 * 160 * 4 (Bytes) == 0x00096000
		BNE PIXEL
		
		; Here is starting point of Function 1, Converting to RGB

	    MOV R4, #0x30000000 ; From 0x30000000 to value of R3 (0x30096000)
		MOV R5, #0x31000000 ; Memory address of "Storing RGB Byte"
RGB_END
		CMP R4, R3 ; If R3 == R4 == 0x30096000, Converting is over
		BEQ FUNC_END
		
RGB
		LDRB R6, [R4], #1 ; Load R of RGBA
		LDRB R7, [R4], #1 ; Load G of RGBA
		LDRB R8, [R4], #1 ; Load B of RGBA
		MOV R9, #0 ; We will store RGB here
		ADD R4, R4, #1 ; Skip A of RGBA
        AND R6, R6, #0xE0 ; Extract R[7:5] (0xE0 == 11100000)
		AND R7, R7, #0xE0 ; Extract G[7:5]
		LSR R7, R7, #3 ; Shift to make RGB
		AND R8, R8, #0xC0 ; Extract B[7:6] (0xC0 == 11000000)
		LSR R8, R8, #6 ; Shift to make RGB
		ADD R9, R9, R6 ; R6 + R7 + R8 = RGB
		ADD R9, R9, R7
		ADD R9, R9, R8
		STRB R9, [R5], #1 ; Store RGB Byte
		B RGB_END ; Check it is over
		
FUNC_END
		END