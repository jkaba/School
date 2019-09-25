		AREA remove, CODE, READONLY
		ENTRY

eos		EQU 	0x00								;Define null constant for comparison use
t		EQU 	0x74								;Define 't' for comparison use
spce 	EQU 	0x20								;Define ' ' (space) for comparison use
byte	EQU 	8									;Define # of bits in 1 byte

		ADR		r1, STRING1							;Let r1 be a pointer to string 1
		ADR		r2, STRING2							;Let r2 pointer to string 2
		LDR		r3, =0x74686520						;Store "the " for comparison use 
		
													;CASE 1 - beginning of sentence
		LDRB 	r5, [r1]							;Load the first character from string 1
		CMP		r5, #t								;Is the character 't'?
		BEQ		check								;If yes, branch to check if "he " or "he\0" follows 

													;LOOP
loop	LDRB 	r5, [r1], #1						;Load a character from string 1, increment pointer after
		STRB 	r5, [r2], #1						;Store the character, increment pointer after
													
													;CASE 2 - end of sentence
		CMP		r5, #eos							;Check if it's the eos character 
		BEQ		inf									;If yes, skip to the end of the program
		CMP		r5, #spce							;If no, check if it's a space. If so, "the " or "the\0" may follow				
		BNE		loop								;UNTIL character is a space	
										
													;Either we are at the start of the sentence or the character is a space
check	MOV		r6, r1								;Save the current position of the pointer for string 1, in case we need to go back
		MOV		r4, #0								;Reset r4, as we will make it point at a substring of the next 4 characters in string 1

build	LDRB 	r5, [r1], #1						;Build the substring by adding one character at a time
		CMP		r5, #eos							;Check if the character is eos character
		LDREQ 	r3, =0x74686500						;If eos and the substring equals "the\0", it will be removed from the string
		ADD		r4, r5								;Append the character to the substring
		CMP		r4, #0x10000000						;Check if the substring contains less than 4 characters
		LSLLT 	r4, #byte							;If yes then shift the substring 1 byte left
		BLT		build								;And continue building the substring (else, the substring is built)
										
		CMP		r4, r3								;Check if substring is "the " or "the\0" (if equal, then the substring must be removed)
		SUBEQ 	r1, #1								;If equal, decrement the pointer to string 1 in order to preserve space or null character 
		MOVNE 	r1, r6								;Else, the substring should not be removed so return the pointer to string 1 back to initial position

		B 		loop								;Repeat processing until string 1's eos character is reached
		
inf		B		inf									;End program with an infinite loop to prevent error

STRING1 DCB 	"the the the 123 the" 				;String 1 
EoS		DCB 	0x00 								;End of string 1
STRING2 SPACE 	0xFF								;The string with "the" removed
		
		ALIGN
		END