# Assignment 3

## Program Goals
• Get hands-on experience in developing mutual exclusion / semaphore / critical section techniques/algorithms.
• Gain more experience with the C programming language from an OS’s mutual exclusion / semaphore / critical section perspective.

## Assignment Description:
Using C programming language, you will be developing a mutual exclusion algorithm for a given process synchronization problem. You need to make sure that your mutual exclusion algorithm ensures that only one process can access the critical section portion of your code at a given point in time. You are not allowed to use any mutual exclusion / semaphore related C systems calls.

## Part 1: Process Creation

Create a total of ten processes: 1 parent process, and 9 children processes. Each of the process will eventually enter into the critical section part of your code.

## Part 2: Critical Section
Implement the following function which you can consider as the critical section of your code:

int critical_section (int loop_limit, int who_called) {
    for (loop limit)
        printf (who_called, loop index);
        printf (“returning to caller process x”); //x is the caller process
    return 0;
}

Conceptually, you can consider the above function critical_section(int, int) as the critical section portion of your code. In this function, loop_limit is the number of iterations and who_called represents the unique process number of the caller process.

## Part 3: Semaphore
You need to implement a semaphore (i.e., flag / mutual exclusion) mechanism to implement the mutual exclusion that will be needed to allow no two processes access the critical section simultaneously. The value of consider a simple semaphore technique (0 or 1) that could be used as a flag so that the processes that are willing to enter into the critical section (i.e., executing the critical_section function) will either wait or execute (wait if flag is 1, and execute if flag is 0).
