# Assignment 1

## Program Goals
• Get experience with the fork(), wait(), execl(), execlp(), pipe(), and dup2() system functions
• Learn more about how operating systems are structured and how a shell works
• Gain more experience with the C programming language from an OS perspective

## Part 1: Parent and Child Process

Write a program in C that will perform the following tasks:
1. Your program will create a parent process which will create three child processes (e.g., child_1, child_2, and child_3)
2. child_1 will create its own child child_1.1
3. parent will wait for child_2 to complete before creating child_3
4. Inside child_3, a system call to an external program will be made

## Part 2: Inter-Process Communication

Write a C program that will accept two integer values from the user as input (for example, X and Y). Your program will create a parent and child where the parent process will read X and the child process will read Y. Now, parent and child processes will exchange X and Y by communicating each other through a pipe

## Part 3: I/O Redirection

Write a program in C that allows shell command “ls -l | grep xxxx” to execute. To do this, your program will create a parent and a child process. Parent process will handle ls -l command and the child process will handle grep xxxx command.
