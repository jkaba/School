		AREA Palindrome, CODE, READONLY
		ENTRY
	
		LDR		r0, =STRING			;Set r0 to point to the string
		LDR 	r5, =EoS			;Set r5 to point to EoS
		MOV 	r1, #-1				;Set pointer in r1 to -1 (incremented later to 0)
toLower	EQU		32					;Add 32 to convert uppercase to lowercase letters in ASCII
		
									;LOOP
LEN		LDRB 	r3, [r0,r2]			;Load a byte of the string (character at position pointed at by r2)
		CMP		r3,	r5				;Check if the character is the null character (end of string)
		BEQ		Check				;If so, stop length count and exit loop
		ADD		r2, #1				;Else, increment pointer to point to next character
		B 		LEN					;UNTIL end of string is reached & r2 points at EoS
	
									;Pointers of r1 and r2 are located at opposite ends of the string
Check	CMP		r1, r2				;Check if pointers have crossed paths yet
		BGT		IsPal				;If so, string is a palindrome as letter pairs have all matched
		ADD		r1, #1				;Increment pointer at the start of the string
		SUB		r2, #1				;Decrement pointer at the end of the string
		
									;LOOP
Char1	LDRB 	r3, [r0,r1]			;Get character 1 at position pointed at by r1
		CMP		r3, #'A'			;Check if character 1 is possibly not a letter
		ADDLT 	r1, #1				;If possibly not a letter, increment this pointer
		BLT		Char1				;Get next character
		
		CMP 	r3, #'z'			;Check if character is greater than 'z'
		ADDGT 	r1, #1				;If so, character is not a letter so increment pointer and get next character
		BGT 	Char1				;UNTIL character is a letter

		CMP		r3, #'a'			;Check if character 1 is uppercase
		ADDLT 	r3, #toLower		;If so, add 32 to convert character to lowercase equivalent
		
									;LOOP
Char2	LDRB 	r4, [r0,r2]			;Get character 2 at position pointed at by r2
		CMP 	r4, #'A'			;Check if character 2 is possibly not a letter
		SUBLT 	r2, #1				;If possibly not a letter, decrement this pointer
		BLT 	Char2				;Get next character
		
		CMP 	r4, #'z'			;Check if character 2 is greater than 'z'
		SUBGT 	r2, #1				;If so, character is not a letter so decrement pointer and get next character
		BGT 	Char2				;UNTIL character is a letter

		CMP 	r4, #'a'			;Check if character 2 is uppercase 
		ADDLT 	r4, #toLower		;If so, add 32 to convert character to lowercase equivalent
							
									;Now r3 and r4 contain two lowercase letters
		CMP 	r3, r4				;Compare character 1 and character 2
		BEQ 	Check				;If equal, the string is possibly a palindrome. Continue comparing character pairs.

									;If they are not equal, the string is not a palindrome
     	MOV 	r0, #0 				;Set r0 to 0 to indicating that the string is not a palindrome
		B 		Loop 				;Skip to end

IsPal	MOV		r0, #1 				;Set r0 to 1 indicating that the string is a palindrome
Loop	B 		Loop 				;Infinite loop to prevent error

STRING	DCB		"Noon"				;String to be tested 
EoS		DCB 	0x00				;End of string ASCII value
		
		END