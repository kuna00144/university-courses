		AREA RESET, DATA, READONLY
		AREA OPT_GRAY, CODE, READONLY
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
		
; ---------- Here is starting point of Function 2, Converting to Grayscale ----------

 		STMFA R13!, {R1, R2, R3, R4} ; Store original state at stack to extract PIXEL
		MOV R6, #0x30000000 ; Memory address for loading 'R'
		MOV R7, #0x31000000 ; Memory address for loading 'G'
		MOV R8, #0x32000000 ; Memory address for loading 'B'
		MOV R1, #0x25000000 ; Memory address for storing Binary bits	
GRAYSCALE
		LDRB R2, [R6], #1 ; Load R of RGBA
		LDRB R3, [R7], #1 ; Load G of RGBA
		LDRB R4, [R8], #1 ; Load B of RGBA 
		MOV R9, #0 ; We will store ( max{R, G, B} + min{R, G, B} ) here
        CMP R2, R3 ; Compare R with B
		BLS G_IGT_R ; G > R
		
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
		BGE R_AND_B 
		B R_AND_G
		
G_IS_MAX ; G > R, B
		CMP R2, R4
		BGE G_AND_B 
		B R_AND_G	
		
R_AND_B ; R > G > B
		ADD R9, R9, R2
		ADD R9, R9, R4
		B CALCUL
		
R_AND_G ; R > B > G
		ADD R9, R9, R2 
		ADD R9, R9, R3
		B CALCUL
		
G_AND_B ; G > R > B
		ADD R9, R9, R3
		ADD R9, R9, R4		

CALCUL
		LSR R9, R9, #1
		STRB R9, [R1], #1
		CMP R5, R8 ; If not R5 != R8 == 0x30096000
		BNE GRAYSCALE ; If R5 != R8 == 0x30096000, Function not finished! Go to GRAYSCALE
		LDMFA R13!, {R1, R2, R3, R4} ; Load original state
		END