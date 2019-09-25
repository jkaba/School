# Name: Jameel Kaba
# UWO ID: jkaba
# Student #: 250796017
# CS3350 Assignment 2 Question 3

    .text                   # begin text segment,
    .globl main             # so "main" can be found

main:                       # Main method
    li    $a0, 1            # a0 = m = 1
    li    $a1, 3            # a1 = n = 3
    la    $v1, resultValue  # Load address of result value into v1
    jal   Ackermann         # Call Ackermann(m, n)

exit:                       # Exit block

    la    $a0, p1           # load a string into a0
    li    $v0, 4            # Set v0 to 4 to print the string
    syscall                 # Print the string into console

    sw    $v1, resultValue  # Save v1, into result value
    lw    $a0, resultValue  # Load result value into a0
    li    $v0, 1            # Set v0 to 1 to print an int
    syscall                 # print result value into console

    li    $v0, 10           # Set to exit program
    syscall                 # Finish program

# Ackermann function
# Call with m in $a0, n in $a1. Result A(m,n) will be stored in $v1.
Ackermann:

    addi $sp, $sp, -12      # Making room on stack pointer
    sw    $ra, 0($sp)       # Saving ra onto stack
    sw    $s0, 4($sp)       # Saving s0 onto stack
    sw    $s1, 8($sp)       # Saving s1 onto stack

    # Case 1: m = 0
    bne   $a0, $0, elseif   # If m is not equal to 0, check next case
    addi $v1, $a1, 1        # answer = n + 1
    j     return            # Go to return branch

elseif:                     # Case 2: m > 0 & n = 0
    bne   $a1, $0, else     # If n does not equal 0, check next case
    addi $a0, $a0, -1       # m = m-1
    li    $a1, 1            # n = 1
    jal   Ackermann         # call ackermann function for (m-1, 1)
    j     return            # Go to return branch

else:                       # Case 3: m > 0 and n > 0
    addi $a1, $a1, -1       # n = n - 1
    move  $s0, $a0          # save m into s0
    jal   Ackermann         # call ackermann function for (m, n-1)
    addiu $a0, $s0, -1      # m = m - 1
    move  $a1, $v1          # n = result of earlier A(m, n-1)
    jal   Ackermann         # call ackermann function for (m-1, A(m, n-1))

return:                     # Return to where function call was made
    lw    $ra, 0($sp)       # load ra
    lw    $s0, 4($sp)       # load s0
    lw    $s1, 8($sp)       # load s1
    addi $sp, $sp, 12       # reset stack pointer
    jr    $ra               # Exit back to where call was made

#--------------------------------------------------------------------#
    .data                   # Data part to store 1 string and the result value

resultValue: .space   100
p1: .asciiz "Ackermann Funtion A(m, n) for A(1, 3) = "