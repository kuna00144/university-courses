		AREA RESET, DATA, READONLY
		AREA Image_Bi, CODE, READONLY

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
		CMP R5, #614400 ; 614400 = 960 * 160 * 4 (Bytes)
		BNE PIXEL
		
		; Here is starting point of Function 3, Converting to Binary
		
	    MOV R4, #0x30000000 ; From 0x30000000 to value of R3 (0x30096000)
		MOV R5, #0x31000000 ; Memory address of "Storing Binary Byte"
		MOV R10, #0 ; Register storing binary bits (8 Binary Pixel = 1 Byte)
		MOV R11, #7 ; Value for shift to combine binary bits
		
BINARY_END	
		CMP R4, R3 ; If not R4 != R3 == 0x30096000
		BNE BINARY ; Need more operation, Go to BINARY
		B FUNC_END ; Else if R4 == R3 == 0x30096000, Function finished! Go to FUNC_END
		
BINARY
		LDRB R6, [R4], #1 ; Load R of RGBA
		LDRB R7, [R4], #1 ; Load G of RGBA
		LDRB R8, [R4], #1 ; Load B of RGBA 
		MOV R9, #0 ; We will store ( max{R, G, B} + min{R, G, B} ) here
		ADD R4, R4, #1 ; Skip A of RGBA
        CMP R6, R7 ; Compare R with B
		BGE R_IGT_G ; R >= G
        B G_IGT_R ; R < G
		
R_IGT_G ; R >= G
		CMP R6, R8
		BGE R_IS_MAX ; R > G, B
		B G_AND_B ; B > R > G
		
G_IGT_R ; G > R
		CMP R7, R8
		BGE G_IS_MAX ; G > R, B
		B R_AND_B ; B > G > R
		
R_IS_MAX ; R > G, B
		CMP R7, R8
		BGE R_AND_B ; R > G > B
		ADD R9, R9, R6 ; R > B > G
		ADD R9, R9, R7
		B CALCUL
		
G_IS_MAX ; G > R, B
		CMP R6, R8
		BGE G_AND_B ; G > R > B
		ADD R9, R9, R6 ; G > B > R
		ADD R9, R9, R7
		B CALCUL
		
R_AND_B
		ADD R9, R9, R6
		ADD R9, R9, R8
		B CALCUL
		
G_AND_B
		ADD R9, R9, R7
		ADD R9, R9, R8
		B CALCUL
		
CALCUL
		LSR R9, R9, #1
        CMP R9, #128
		BGE BI_1 ; If R9 > 127, Current binary bit is 1
		MOV R9, #0 ; Else if R9 <= 127, Current binary bit is 0
		B BI_SHIFT
		
BI_1
		MOV R9, #1 ; R9 > 127, Current binary bit is 1
		
BI_SHIFT
		ADD R10, R10, R9, LSL R11
		CMP R11, #0 ; If R11 == 0, R11 = 7
		BEQ BI_STORE
		SUB R11, R11, #1 ; R11 -= 1
		B BINARY
		
BI_STORE
		STRB R10, [R5], #1
		MOV R10, #0
		MOV R11, #7
		B BINARY_END
		
FUNC_END
		END