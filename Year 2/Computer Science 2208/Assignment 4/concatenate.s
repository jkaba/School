		AREA concatenate, CODE, READONLY
		ENTRY

eos		EQU		0x00							;Define the end of string character for comparison use
		ADR 	r1, STRING1						;Let r1 be a pointer to STRING1 (string to be concatenated)
		ADR 	r2, STRING2						;Let r2 be a pointer to STRING2 (string to be concatenated)
		ADR 	r3, STRING3						;Let r3 be a pointer to STRING3 (string that holds the resulting concatenation)

												;LOOP
first	LDRB 	r4, [r1], #1					;Load a byte from string 1, and then point to the next byte
		CMP 	r4, #eos						;Check if the byte is the EoS character
		STRBNE	r4, [r3], #1					;If not, append the byte to string 3, and then point to the next byte in string 3
		BNE 	first							;Until EoS character is reached

												;LOOP
second	LDRB 	r4, [r2], #1					;Load a byte from string 2, and then point to the next byte
		STRB 	r4, [r3], #1					;Append the byte to string 3, and then point to the next byte in string 3
		CMP 	r4, #eos						;Check if the last byte that was appended was the EoS character
		BNE 	second							;Until the EoS character is appended to the concatenation string

loop 	B 		loop							;End program with an infinite loop to prevent error

STRING1 DCB 	"this is test string1"			;String1
EosS1	DCB 	0x00							;End of string1
STRING2 DCB 	"this is test string2"			;String2
EoS2 	DCB 	0x00							;End of string2
STRING3 space 	0xFF							;Space reserved for string3
	
		END