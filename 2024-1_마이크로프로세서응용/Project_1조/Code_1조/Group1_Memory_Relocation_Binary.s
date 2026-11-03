		AREA RESET, DATA, READONLY
		AREA MEM_RELOC_BINARY, CODE, READONLY
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
		MOV R11, #0 ; ZERO
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
		
; ---------- Here is starting point of Function 3, Converting to Binary ----------
		
		STMFA R13!, {R1, R2, R3, R4} ; Store original state at stack to extract PIXEL
		MOV R6, #0x30000000 ; Memory address for loading 'R'
		MOV R7, #0x31000000 ; Memory address for loading 'G'
		MOV R8, #0x32000000 ; Memory address for loading 'B'
		MOV R1, #0x25000000 ; Memory address for storing Binary bits
		MOV R10, #0 ; Register storing binary bits (8 Binary Pixel = 1 Byte)
		MOV R11, #7 ; Value for shift to combine binary bits
		
BINARY_END	
		CMP R5, R8 ; If not R5 != R8 == 0x30096000
		B FUNC_END ; Else if R5 == R8 == 0x30096000, Function finished! Go to FUNC_END
		BNE BINARY ; Need more operation, Go to BINARY
		
BINARY
		LDRB R2, [R6], #1 ; Load R of RGBA
		LDRB R3, [R7], #1 ; Load G of RGBA
		LDRB R4, [R8], #1 ; Load B of RGBA 
		MOV R9, #0 ; We will store ( max{R, G, B} + min{R, G, B} ) here
        CMP R2, R3 ; Compare R with B
		BGE R_IGT_G ; R >= G
        B G_IGT_R ; R < G
		
R_IGT_G ; R >= G
		CMP R2, R4
		BGE R_IS_MAX ; R > G, B
		B G_AND_B ; B > R > G
		
G_IGT_R ; G > R
		CMP R3, R4
		BGE G_IS_MAX ; G > R, B
		B R_AND_B ; B > G > R
		
R_IS_MAX ; R > G, B
		CMP R3, R4
		BGE R_AND_B ; R > G > B
		ADD R9, R9, R2 ; R > B > G
		ADD R9, R9, R3
		B CALCUL
		
G_IS_MAX ; G > R, B
		CMP R2, R4
		BGE G_AND_B ; G > R > B
		ADD R9, R9, R2 ; G > B > R
		ADD R9, R9, R3
		B CALCUL
		
R_AND_B
		ADD R9, R9, R2
		ADD R9, R9, R4
		B CALCUL
		
G_AND_B
		ADD R9, R9, R3
		ADD R9, R9, R4
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
		CMP R11, #0 ; If R11 == 0, it is last bit of 8 Binary bits
		BEQ BI_STORE
		SUB R11, R11, #1 ; Else if R11 != 0, R11 -= 1
		B BINARY
		
BI_STORE ; 8 Binary bits loaded, Time to store!
		STRB R10, [R1], #1
		MOV R10, #0 ; Initializing to continue loading and storing
		MOV R11, #7
		B BINARY_END
		
FUNC_END
		LDMFA R13!, {R1, R2, R3, R4} ; Load original state
		END