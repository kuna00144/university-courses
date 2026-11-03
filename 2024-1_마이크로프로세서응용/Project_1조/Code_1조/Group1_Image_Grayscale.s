      AREA RESET, DATA, READONLY
      AREA Image_Gray, CODE, READONLY
	  ; Instead of EXPORT, we add loading function before main function (Grayscale function)
      ENTRY   
      ; Initializing
      MOV R1, #0x40000000 ; Starting Address of Input (Image)
      MOV R2, #0x20000000 ; Address of "Memory storing HEADER" and "End of Header"
      MOV R3, #0x30000000 ; Address of "Memory storing PIXEL" and "End of PIXEL"
      MOV R4, #0          ; Clear register to use for loading and storing
      MOV R5, #0          
      MOV R10, #0 
      B HEADER
      
HEADER_END ; Judge the end of header, "IDAT"
      SUB R2, R2, #2 ; Prepare to judge "IDAT"
      MOV R7, #0
      LDRB R4, [R2], #-1 ; Compare with 'A'
      MOV R6, R4
      CMP R6, #0x41
      ADDNE R7, R7, #1 ; If it is not 'A', Check at R7
      LDRB R4, [R2], #-1 ; Compare with 'D'
      MOV R5, R4
      CMP R5, #0x44
      ADDNE R7, R7, #1 ; If it is not 'D', Check at R7
      LDRB R4, [R2], #-1 ; Compare with 'I'
      CMP R4, #0x49
      ADDNE R7, R7, #1 ; If it is not 'I', Check at R7
      STRB R4, [R2, #1]! ; Restore to its original state
      STRB R5, [R2, #1]!
      STRB R6, [R2, #1]!
      ADD R2, R2, #2
      CMP R7, #0
      MOV R5, #0 ; Reset R5 to use
      BEQ PIXEL ; If Last 4 bits are "IDAT", Go to PIXEL
      
HEADER ; Store bits of header from image
      LDRB R4, [R1]
      STRB R10, [R1], #1
      MOV R5, R4
      STRB R4, [R2], #1
      CMP R5, #0x54 ; Check if current bit is 'T' of "IDAT"
      BNE HEADER
      B HEADER_END

PIXEL ; Store bits of pixel from image
      LDRB R4, [R1]
      STRB R10, [R1], #1
      STRB R4, [R3], #1
      ADD R5, R5, #1
      CMP R5, #614400 ; Total number of bytes = 960 * 160 * 4 (Bytes)
      BNE PIXEL
      
	  ; Here is starting point of function 2, Converting to grayscale
	  
      MOV R1, #0x30000000       ; Start address of PIXEL data
      MOV R2, #0x32000000       ; Destination address for Grayscale data

Grayscale
     LDRB  R4, [R1], #1          ; Load 'R' of RGBA
     LDRB  R5, [R1], #1          ; Load 'G' of RGBA
     LDRB  R6, [R1], #1          ; Load 'B' of RGBA
     ADD   R7, R4, R5            ; R7 = R + G + B
     ADD   R7, R7, R6
     ; We will divide by 3 using subtraction loop
     MOV   R8, #0                ; Initializing register to store result of division
     MOV   R9, #3                ; Divisor = 3

Divide_by_3
     CMP   R7, R9                ; Check if R7 >= R9
     SUBCS R7, R7, R9            ; R7 -= R9 (Subtraction if carry set)
     ADDCS R8, R8, #1            ; R8 += 1 (Increment result if carry set)
     BCS   Divide_by_3           ; Loop back if carry set

     STRB  R8, [R2], #1          ; Store the Grayscale value
     ADD   R1, R1, #1            ; Skip 'A' of RGBA
     CMP   R1, R3                ; Check if it is end of PIXEL data
     BLT   Grayscale             ; If it is not end of data, continue

     END