		AREA RESET, DATA, READONLY
		AREA OPT_RGB, CODE, READONLY
		ENTRY
		; Instead of EXPORT, We add loading function code before main function code
		; Initialization
		MOV R1, #0x40000000 ; Starting Address of Input (Image)
		MOV R2, #0x20000000 ; Memory Address of "Storing HEADER"
		MOV R3, #0x30000000 ; Memory Address of "Storing R"
		MOV R4, #0x31000000 ; Memory Address of "Storing G"
		MOV R5, #0x32000000 ; Memory Address of "Storing B"
		MOV R6, #0          
		MOV R7, #0	
HEADER ; Store bytes of HEADER from image
		LDRB R6, [R1], #1
		MOV R7, R6
		STRB R6, [R2], #1
		CMP R7, #0x54 ; Check that current byte is 'T' 
		BNE HEADER ; If it is not 'T', keep loading	
HEADER_END ; Check "IDAT"
		; We will check 3 bytes before 'T'
		SUB R2, R2, #2
		MOV R10, #0
		LDRB R6, [R2], #-1 ; Check if it is 'A'
		CMP R6, #0x41
		ADDNE R10, R10, #1 ; If it is not 'A', mark at R10
		LDRB R6, [R2], #-1 ; Check if it is 'D'
		CMP R6, #0x44
		ADDNE R10, R10, #1 ; If it is not 'D', mark at R10
		LDRB R6, [R2], #-1 ; Check if it is 'I'
		CMP R6, #0x49
		ADDNE R10, R10, #1 ; If it is not 'I', mark at R10
		; Restore to original state
		ADD R2, R2, #5
	    CMP R10, #0 ; If R10 != 0, it is not "IDAT"
		BNE HEADER ; If it is "IDAT", terminate loading HEADER and start loading PIXEL
		MOV R7, #0 ; Initializing register to store PIXEL	
PIXEL ; Store bytes of PIXEL from image
		LDRB R6, [R1], #1 ; Store R of RGBA
		STRB R6, [R3], #1
		LDRB R6, [R1], #1 ; Store G of RGBA
		STRB R6, [R4], #1
		LDRB R6, [R1], #2 ; Store B of RGBA and skip A of RGBA
		STRB R6, [R5], #1
		ADD R7, #4
		CMP R7, #614400 ; 614400 = 960 * 160 * 4 (Bytes)
		BNE PIXEL

		; Here is starting point of Function 1, Convert to RGB

        MOV R7, #0x30000000 ; Memory address of R
        MOV R8, #0x31000000 ; Memory address of G
		MOV R9, #0x32000000 ; Memory address of B
		MOV R11, #0x25000000 ; Memory address of 8-bit RGB
RGB
		MOV R10, #0 ; We will store RGB here
		LDRB R6, [R7], #1 ; Load R of RGBA
        AND R6, R6, #0xE0 ; Extract R[7:5]
	    ADD R10, R10, R6	
        LDRB R6, [R8], #1 ; Load G of RGBA
		AND R6, R6, #0xE0 ; Extract G[7:5]
        LSR R6, R6, #3 ; Shift to make RGB
		ADD R10, R10, R6
        LDRB R6, [R9], #1 ; Load B of RGBA
		AND R6, R6, #0xC0 ; Extract B[7:6]
        LSR R6, R6, #6 ; Shift to make RGB
		ADD R10, R10, R6
        STRB R10, [R11], #1 ; Store RGB Byte
       	CMP R9, R5 ; If R9 == R5 , Converting is over
		BNE RGB
		END