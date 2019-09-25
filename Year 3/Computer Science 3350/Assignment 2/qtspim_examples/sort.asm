# Simple routine to demo functions
# ------------------------------------------------------------------
	
	.text

	.globl	main
	
	# FUNCTION: main()
main:
	# initialize testarray, i.e. assign a value to each element of testarray
	# testarray is defined in the data section(at the bottom of this file)
	la	$t0, testarray	        #  load base address of array into register $t0
	li	$t1, 5		        #  $t1 = 5   ("load immediate")
	sw $t1, ($t0)		        #  first array element set to 5; indirect addressing
	li $t1, 13		        #   $t1 = 13
	sw $t1, 4($t0)		        #  second array element set to 13, in 4($t0) "4" means offset of $t0 
	li $t1, 4		        #   $t1 = 4
	sw $t1, 8($t0)		        #  third array element set to 4
	li $t1, 6		        #   $t1 = 6
	sw $t1, 12($t0)		        #  forth array element set to 6
	li $t1, 3		        #   $t1 = 3
	sw $t1, 16($t0)		        #  fifth array element set to 3
	
	# assign arguments and  call function
	move $a0, $t0     # load address to $a0, i.e. the first argument of function sort
   	lw $a1, size      # load word to $a1, i.e. the second argument of function sort
   	jal sort          #call function
	
	#call system function to exit main function
	li $v0, 10        # Sets $v0 to "10" to select exit syscall
	syscall           # Exit

# ------------------------------------------------------------------
	
	# FUNCTION: sort(int v[], int n)
	# Arguments are stored in $a0 and $a1
		# array "v" is stored in $a0
		# integer "n" is stored in $a1
	# Return address is stored in $ra (put there by jal instruction)
	
	#Saving registers
sort:   addi $sp, $sp, -20 # make room on stack for 5 registers
	sw $ra, 16($sp)# save $ra on stack
	sw $s3,12($sp) # save $s3 on stack
	sw $s2, 8($sp)# save $s2 on stack
	sw $s1, 4($sp)# save $s1 on stack
	sw $s0, 0($sp)# save $s0 on stack

	#Procedure body

        # 1).Move parameters
	move $s2, $a0 # copy parameter $a0 into $s2 (save $a0)
	move $s3, $a1 # copy parameter $a1 into $s3 (save $a1)
        
	# 2).Outer loop
	move $s0, $zero  # i = 0
for1tst:slt $t0, $s0,$s3 #reg$t0=0if$s0Š$s3(iŠn)
	beq $t0, $zero, exit1 # go to exit1 if $s0 Š $s3 (i Š n)
	
	# 3). Inner loop
	addi $s1, $s0, -1  # j = i – 1
for2tst:slti $t0, $s1,0    #reg$t0=1if$s1<0(j<0)
	bne $t0, $zero, exit2  # go to exit2 if $s1 < 0 (j < 0)
	sll $t1, $s1, 2        # reg $t1 = j * 4
	add $t2, $s2, $t1      # reg $t2 = v + (j * 4)
	lw  $t3, 0($t2)        # reg $t3 = v[j]
	lw  $t4, 4($t2)        # reg $t4 = v[j + 1]
	slt $t0, $t4, $t3      # reg $t0 = 0 if $t4 Š $t3
	beq $t0, $zero, exit2  # go to exit2 if $t4 Š $t3

	# 4). Pass parameters and call
	move $a0, $s2  # 1st parameter of swap is v (old $a0)
	move $a1, $s1  # 2nd parameter of swap is j
 	jal swap       # swap code shown in Figure 2.25


	# 5). Inner loop
	addi $s1, $s1, -1  # j –= 1
	j for2tst          # jump to test of inner loop

	# 6). Outer loop
exit2:  addi $s0, $s0, 1   # i+=1
        j    for1tst  # jump to test of outer loop


	# Restoring registers
exit1: lw $s0, 0($sp)  # restore $s0 from stack
       lw $s1, 4($sp)  # restore $s1 from stack
       lw $s2, 8($sp)  # restore $s2 from stack
       lw $s3,12($sp)  # restore $s3 from stack
       lw $ra,16($sp)  # restore $ra from stack
       addi  $sp,$sp, 20 # restore stack pointer

	# Procedure return
	jr $ra # return to calling routine

# ------------------------------------------------------------------
	
	# FUNCTION: swap(int v[], int k)
	# In this function it will swap v[k] and v[k+1]
	# Arguments are stored in $a0 and $a1
		# array "v" is stored in $a0
		# integer "k" is stored in $a1
	# Return address is stored in $ra (put there by jal instruction)

	# Procedure body
swap:   sll $t1, $a1, 2  # reg $t1 = k * 4
	add $t1, $a0, $t1 # reg $t1 = v + (k * 4)
			  # reg $t1 has the address of v[k]
	lw $t0, 0($t1) # reg $t0 (temp) = v[k]
	lw $t2, 4($t1) # reg $t2 = v[k + 1]
			# refers to next element of v
	sw $t2, 0($t1) # v[k] = reg $t2
	sw $t0, 4($t1) # v[k+1] = reg $t0 (temp)

	#Procedure return
	jr $ra  # return to calling routine


#----------------------------------------------------------

	# Start .data segment (data!)
	.data
testarray:		.space	20		#  declare 20 bytes of storage to hold array of 5 integers
						#  we will pass this array to "sort" function as the first argument

size:	.word 5					# declare a word with value 5
						#  we will pass this value to "sort" function as the second argument
