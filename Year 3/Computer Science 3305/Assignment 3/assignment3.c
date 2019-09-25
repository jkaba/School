/*
 Name: Jameel Kaba
 UWO id: jkaba
 Student #: 250796017
 
 CS3305B Assignment 3
 Part 3: I/O Redirection
 This program runs a mutual exclusion algorithm for a
 a given process synchronization problem.
 
 As a note, this program may run weirdly on linux.
 For some reason the command prompt will appear either during the program,
 or before the output is printed. This leads to the command prompt looking like
 it is frozen, but it is not.
 */

/* include statements */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/* Initialize semaphore and pipe */
int semaphore = 0;
int fd[2];

/* Method header */
int critical_section (int loop_limit, int who_called);

int main(){
    
    /* Initialize variables */
    int i = 0;
    int loopLimit = 10;
    pid_t pid;
    pid_t parent;
    
    /* Get parent ready */
    if(pipe(fd) < 0){
        exit(1);
    }
    
    /* Write the value of semaphore into the pipe */
    write(fd[1], &semaphore, sizeof(semaphore));
    
    /* Create the parent */
    pid = fork();
    
    /* If pid < 0, then we have an error */
    if (pid < 0){
        perror("fork()");
        printf("main function: errno number is %d\n",errno);
        exit(pid);
    }
    
    /* If pid > 0, then we are in the parent */
    if(pid > 0){
        
        /* Save the parent's pid */
        parent = getpid();
        
        /* Read the value of semaphore */
        read(fd[0], &semaphore, sizeof(semaphore));
        
        /* While the semaphore is 1, the crit section is in use */
        while(semaphore){
            
            /* Continue to read semaphore value from pipe, until crit section is free */
            read(fd[0], &semaphore, sizeof(semaphore));
        }
        
        /* If the semaphore is 0 */
        if(!semaphore){
            
            /* Set semaphore to 1, as crit section as in use */
            semaphore = 1;
            
            /* Write the semaphore value into the pipe */
            write(fd[1], &semaphore, sizeof(semaphore));
            
            /* Run the critical section with the parent */
            critical_section(loopLimit, parent);
            
            /* Print new line for formatting */
            printf("\n");
            
            /* Set semaphore to 0, as crit section not in use */
            semaphore = 0;
            
            /* Write the semaphore value into the pipe */
            write(fd[1], &semaphore, sizeof(semaphore));
        }
        
        /* Child process block that creates 9 children and runs crit section */
        for(i = 0; i < 9; i++) {
            
            /* Check to see if we are in the parent */
            if(getpid() == parent){
                
                /* Create a child process */
                pid = fork();
                
                /* If pid = 0, then we are in the child */
                if(pid == 0){
                    
                    /* Read the semaphore value from the pipe */
                    read(fd[0], &semaphore, sizeof(semaphore));
                    
                    /* While the semaphore is 1, the crit section is in use */
                    while(semaphore){
                        
                        /* Continue to read semaphore value from pipe, until crit section is free */
                        read(fd[0], &semaphore, sizeof(semaphore));
                    }
                    
                    /* If the semaphore is 0 */
                    if(!semaphore){
                        
                        /* Set the semaphore to 1, as the crit section is in use */
                        semaphore = 1;
                        
                        /* Write the semaphore value into the pipe */
                        write(fd[1], &semaphore, sizeof(semaphore));
                        
                        /* Run the critical section with the child */
                        critical_section(loopLimit, getpid());
                        
                        /* Print a new line for formatting */
                        printf("\n");
                        
                        /* Set the semaphore to 0, as the crit section is not in use */
                        semaphore = 0;
                        
                        /* Write the semaphore value into the pipe */
                        write(fd[1], &semaphore, sizeof(semaphore));
                    }
                    /* Wait for process to terminate */
                    wait(NULL);
                }
            }
        }
    }
    /* Return 0 to end the program */
    return 0;
}

/* Critical section method */
int critical_section (int loop_limit, int who_called) {
    
    /* j represents the loop index */
    int j;
    
    /* For loop that prints out who called and what the loop index is */
    for (j = 0; j < loop_limit; j++){
        printf("who called: %d, index %d\n", who_called, j);
    }
    
    /* Print a returning message that includes what process we're returning to */
    printf("returning to caller process %d\n", who_called); //x is the caller process
    
    /* Return 0 to go back to the caller process */
    return 0;
}
