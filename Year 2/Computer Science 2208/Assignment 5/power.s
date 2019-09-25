		AREA power, CODE, READONLY

x		EQU 	2						;Set the value for the base x
n		EQU 	12						;Set the value for the parameter, exponent n 
up		EQU 	4						;Set the value to increment the stack
	
		ENTRY							;Main Program
		ADR		sp,Stack				;Define the stack
		MOV		r4,#n        			;Get the value of the exponent and move it in r4
		MOV		r3,#x        			;Get the value of base x and move it r3
		
		STR		r4,[sp,#-up]!			;Push the parameter exponent onto the full descending stack
		SUB 	sp,sp,#up      			;Reserve space on the stack to hold the return value
		
		BL 		Recur					;Calculate the power of x
		LDR 	r0,[sp],#up	    		;Load the result into r0 and pop it off the stack
		ADD 	sp,sp,#up     			;Pop the corresponding parameter from stack

		ADR 	r1,Result     			;Get the address for the result variable
		STR 	r0,[r1]       			;Store the final answer in result variable

Loop 	B 		Loop        			;Infinite loop to prevent error	

;==========================================================================================================

		AREA power, CODE, READONLY
			
Recur 	STMFD 	sp!,{r0,r1,r2,fp,lr} 	;Push general registers, frame pointer, and link register onto stack 
		MOV 	fp,sp         			;Set the frame pointer for function call

		LDR 	r0,[fp,#0x18] 			;Get the exponent parameter from the stack

Base	CMP 	r0,#0        			;Base Case - exponent n = 0
		MOVEQ 	r0,#1        			;If base case is true, then set the return value to 1
		STREQ 	r0,[fp,#0x14]  			;If base case is true, then push return value on stack
		BLEQ 	Return  	     		;If base case is true, then branch to Return 
					
		AND 	r1,r0,#1				;Else, check if exponent is odd or even
		CMP 	r1,#1					;If the exponent is odd, 
		BEQ		Odd						;Then branch to Odd
		BNE		Even					;Else, branch to Even
			
Odd		SUB 	r0,#1					;Subtract 1 from the exponent n
		STR 	r0,[sp,#-up]!			;Push the new value of exponent n onto stack
		SUB 	sp,#up					;Reserve space for the return value 
		
		BL 		Recur					;Recursive call to the Power function with a new n value
		LDR 	r0,[sp],#up				;Load the result value into r0 before popping it from stack
		ADD 	sp,#up					;Pop the parameter exponent value
		MUL 	r1,r0,r3				;Calculate the result value
		STR 	r1,[fp,#0x14]			;Push the result value onto the stack
		BL 		Return					;Branch to Return

Even	LSR 	r0,r0,#1				;Divide exponent by 2
		STR 	r0,[sp,#up]!			;Push new exponent n on stack
		SUB 	sp,#up					;Reserve space for return value
		
		BL 		Recur					;Recursive call to Power function with new n value
		LDR 	r0,[sp],#up				;Load result value into r0 before popping it from stack
		ADD 	sp,#up					;Increment stack pointer
		MOV 	r1,r0					;Copy result value
		MUL 	r2,r1,r0				;Calculate square of Power's return value & store in r2
		STR 	r2,[fp,#0x14]			;Push value onto stack
		BL 		Return					;Branch to Return 
	
Return 	MOV 	sp,fp         			;Collapse the working spaces for function call
		LDMFD 	sp!,{r0,r1,r2,fp,pc} 	;Restore the initial settings of registers and return to caller
		
;==========================================================================================================

		AREA power, DATA, READWRITE
			
Result 	DCD   	0x00					;To hold the result of the calculation for power of x 
		SPACE 	0xB4       				;Reserve space in memory for stack
Stack	DCD   	0x00        			;Initial position of the full descending stack
	
;==========================================================================================================
		END