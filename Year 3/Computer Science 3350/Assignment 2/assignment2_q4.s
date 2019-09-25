# Name: Jameel Kaba
# UWO ID: jkaba
# Student #: 250796017
# CS3350 Assignment 2 Question 4

    .text
    .globl main

main:
	la		$a3, Array              # load pointer to array A
	la		$a1, Second             # load pointer to array B
	lw		$a2, Length             # load length of Array
	jal		mergesort               # Jump to mergesort

Exit:
    la      $a0, p2                 # Load Finished message
    li      $v0, 4                  # Set up the print call
    syscall                         # Print out message

    li      $v0, 10                 # Set up the exit call
    syscall                         # Exit the program

#   void MergeSort(int *B, int *A, int n) {
#       if (n==1) {
#           B[0] = A[0];
#       }
#       else {
#           int* C[n];
#           MergeSort(C, A, n/2);
#           MergeSort(C+n/2, A+n/2, n-n/2);
#           Merge(B, C, C+n/2, n/2, n-n/2);
#   }

mergesort:
	addi	$sp, $sp, -16			# Create space on stack pointer to save
	sw		$ra, 0($sp)				# Save return address
	sw		$a3, 4($sp)				# Save array pointer ($a3)
	sw		$a1, 8($sp)				# Save Second pointer ($a1)
	sw		$a2, 12($sp)			# Save n ($a2)

sort_if:
	bne		$a2, 1, sort_else		# If $a2 != 1 (n != 1) go to else
	lw		$s0, 0($a3)				# Load A[0] into $s0
	sw		$s0, 0($a1)				# B[0] = A[0], save $s0 into B[0]
	j		sort_end				# Sort is done, return from Sort

sort_else:
	srl		$a2, $a2, 1				# $a2 = n/2
	jal		mergesort				# recursive call 1: MergeSort(Second, Array, n/2)

	sll		$a2, $a2, 2				# $a2 = address value of n/2
	add		$a3, $a3, $a2			# $a3 = Array + n/2 --> (A+n/2)
	add		$a1, $a1, $a2			# $a1 = Second + n/2 --> (C+n/2)
	srl		$a2, $a2, 2				# Restore n/2
	jal		mergesort				# recursive call 2: MergeSort(Second+n/2, Array+n/2, n-n/2)
    
	sll		$a2, $a2, 2				# $a2 = address value of n/2
	sub		$a3, $a3, $a2			# Reset array pointer
	sub		$a0, $a1, $a2			# Reset Second pointer
	srl		$a2, $a2, 1				# address value of n/2 -> n
	srl		$t0, $a2, 1				# na = $t0 = n/2
	sub		$t1, $a2, $t0			# nb = $t1 = n-n/2
	jal		merge					# Call the merge method

sort_end:
	lw		$ra, 0($sp)				# Load the return address
	lw		$a3, 4($sp)				# Load the array pointer ($a3)
	lw		$a1, 8($sp)				# Load Second pointer ($a1)
	lw		$a2, 12($sp)			# Load n ($a2)
	addi	$sp, $sp, 16			# Remove the stored stack space
	jr		$ra						# Return back to main

#   void Merge(int *Array, int *FirstHalf, int *SecondHalf, int n) {
#       int na = n/2;
#       int nb = n - na;
#       while (na>0 && nb>0) {
#           if (*FirstHalf <= *SecondHalf) {
#               *Array++ = *FirstHalf++;
#               na--;
#           }
#           else {
#               *Array++ = *SecondHalf++;
#               nb--;
#           }
#       }
#       while (na>0) {
#           *Array++ = *FirstHalf++;
#           na--;
#       }
#       while (nb>0) {
#           *Array++ = *SecondHalf++;
#           nb--;
#       }
#   }

#Array pointer = $a3
#FirstHalf pointer = $a1 = FirstHalf
#SecondHalf pointer = $a0 = SecondHalf
#n = $a2
merge:
	lw		$t2, 0($a0)				# Load the value at FirstHalf into $t2
	lw		$t3, 0($a1)				# Load the value at SecondHalf into $t3

while1:
	beqz	$t1, while2				# If the value of nb = 0, then go to second while
	beqz	$t0, while3				# If the value of na = 0, then go to third while

while1_if:
	bgt		$t2, $t3, while1_else	# If first value is greater than the second value, go to else
	sw		$t2, 0($a3)				# Save the element pointed at by the FirstHalf into the array
	addi	$a3, $a3, 4				# Increment the array pointer
	addi	$a0, $a0, 4				# Increment the FirstHalf pointer
	addi	$t0, $t0, -1			# Decrement the value of na
	j		merge					# Restart the merge method

while1_else:
	sw		$t3, 0($a3)				# Save the element pointed at by the SecondHalf into the array
	addi	$a3, $a3, 4				# Increment the array pointer
	addi	$a1, $a1, 4				# Increment the SecondHalf pointer
	addi	$t1, $t1, -1			# Decrement the value of nb
	j		merge					# Restart the merge method

while2:
	beqz	$t0, merge_end			# If both na and nb are 0, then end the method
	sw		$t2, 0($a3)				# Save the element pointed at by the FirstHalf into the array
	addi	$a3, $a3, 4				# Increment the array pointer
	addi	$a0, $a0, 4				# Increment the FirstHalf pointer
	addi	$t0, $t0, -1			# Decrement the value of na
	j		merge					# Restart the merge method

while3:
	beqz	$t1, merge_end			# If both na and nv are 0, then end the method
	sw		$t3, 0($a3)				# Save the element pointed at by the SecondHalf into the array
	addi	$a3, $a3, 4				# Increment the array pointer
	addi	$a1, $a1, 4				# Increment the SecondHalf pointer
	addi	$t1, $t1, -1			# Decrement the value of nb
	j		merge					# Restart the merge method

merge_end:							# This copies the sorted loop into the Secondary array (B)
	sll		$a2, $a2, 2				# Shift $a2 left by 2 so that it is the address value of n
	sub		$a3, $a3, $a2			# Reset the array pointer
	sub		$a1, $a1, $a2			# Reset the Secondary pointer
	srl		$a2, $a2, 2				# Restore the value of n
	move	$t0, $a2				# Make a temporary copy of n

    la      $a0, p1                 # Set up printing message
    li      $v0, 4                  # Set v0 to print out string
    syscall                         # Print out message

loop:
	beqz	$t0, merge_done			# If the counter is 0, then head to the end
    lw		$s0, 0($a3)				# Load the sorted value into $s0
	sw		$s0, 0($a1)				# Save the sorted value into the Secondary Array (B)

    move    $a0, $s0                # Move value of $s0 into $a0 for printing
    li      $v0, 1                  # Set $v0 up for printing an int
    syscall                         # Print out the sorted value

    la      $a0, space              # Set up printing of a space
    li      $v0, 4                  # Set $v0 up for printing a string
    syscall                         # Print out a space

	add		$a3, $a3, 4				# Increment the array pointer
	add		$a1, $a1, 4				# Increment the Second pointer
	addi	$t0, $t0, -1			# Decrement the counter
    j		loop					# Restart loop to go over sorted elements
	
merge_done:
    la      $a0, eol                # Set up printing for a new line
    li      $v0, 4                  # Set up $v0 for printing a string
    syscall                         # Print out a new line
	jr		$ra						# Return to where call was made

#---------------------------------------------------------------------------#
    	.data

Array:
        .word	29
        .word   45
        .word   9
        .word   25
        .word   6
        .word   33
        .word   22
        .word   51

Second:
        .word	0
        .word   0
        .word   0
        .word   0
        .word   0
        .word   0
        .word   0
        .word   0

Length:
        .word	8

p1:     .asciiz "Sorting Array: "
p2:     .asciiz "Finished Sorting, Sorted Array above.\n"
space:  .asciiz " "
eol:    .asciiz "\n"

