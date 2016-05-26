		AREA polynomial, CODE, READWRITE
		ENTRY
	
										;MAIN PROGRAM
x		EQU 	3						;Choose the value to be computed on
		MOV 	r0, #x					;Store the value of x in r0
		BL 		subrt					;Call subroutine to determine the polynomial 
	
		MOV		r1, r0, LSL#1 			;Double the result returned from the subroutine and store in r0
loop 	B 		loop					;End program with an infinite loop to prevent error

										;SUBROUTINE
subrt 	STMFD 	sp!, {r1-r6}			;Save settings of registers 1-6
		ADR 	r1, a					;Let r1 be a pointer to coefficient a of polynomial
		ADR 	r2, b					;Let r2 be a pointer to coefficient b of polynomial
		ADR 	r3, c					;Let r3 be a pointer to coefficient c of polynomial
		ADR 	r4, clip				;Let r4 be a pointer to clipping limit

		LDR 	r5, [r2]				;Load the value of b into r5
		LDR 	r6, [r3]				;Load the value of c into r6
		MLA 	r2, r5, r0, r6			;Store the result of b*x + c in r2 (Calculate b*x and then add c)

		MOV 	r5, r0					;Load a copy of r0 (x) into r5
		MOV 	r6, r0					;Load a second copy of r0 (x) into r6
		MUL 	r0, r5, r6				;Calculate the value of r0 squared
		LDR 	r5, [r1]				;Load the value of a into r5
		MUL 	r1, r5, r0				;Store the result of a*x^2 in r1

		ADD 	r0, r1, r2				;Calculate a*x^2 + bx + c

		LDR 	r1, [r4]				;Load the value of the clipping limit into r1
		CMP 	r0, r1					;Compare the sum with the clipping limit
		MOVGT 	r0,r1					;If the sum is greater than the clipping limit
										;then replace the sum with the clipping limit 

		LDMFD 	sp!, {r1-r6}			;Restore register settings to how they were before calling the subroutine
		BX 		lr						;Return to the main program

a 		DCD 	-5						;Coefficient a of polynomial (ax^2)
b 		DCD 	6						;Coefficient b of polynomial (bx)
c 		DCD 	7						;Coefficient c of polynomial (c)
clip 	DCD 	10						;Clipping limit (Maximum value that the sum can be)
		
		END				