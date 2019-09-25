/*
 Name: Jameel Kaba
 UWO ID: jkaba
 Student #: 250796017
 
 CS3305B Assignment 1
 Part 2: Inter-Process Communication
 This program requires the user to input 2 integers
 One integer is handeled by the parent, the other
 is handeled by the child.
 Both parent and child share their integer through a pipe
 */

/* include statements */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(){
    
    /* initialize variables */
    int fd[2];
    int fd2[2];
    int valueX = 0;
    int valueY = 0;
    int length;
    int i;
    pid_t pid;
    
    /* Creating pipes */
    if (pipe(fd) < 0 || pipe(fd2) < 0){
        perror("Failed to allocate pipes");
        exit(1);
    }
    
    /* Fork, and check to ensure pid is not 0 */
    if ((pid = fork()) < 0){
        
        /* If pid is < 0, then we have an error and exit */
        perror("Failed to fork process");
        exit(-1);
    }
    
    /* If pid is equal to 0, then we are in the child */
    if (pid == 0){
        
        /* Create an int to store what we get from the pipe */
        int valX = 0;
        
        /* Read the value from the input port of pipe */
        length = read(fd[0], &valX, sizeof(valX));
        
        /* If the length is < 0, we fail to read and exit */
        if (length < 0){
            perror("From child: Failed to read data from pipe");
            exit(1);
        }
        
        /* If the length is 0, we read the end of file from pipe */
        else if (length == 0){
            fprintf(stderr, "From child: Read EOF from pipe");
        }
        
        /* Else, we read something from the pipe */
        else{
            
            /* Ask, the user to input a value for Y */
            printf("\nFrom child: Please enter a value for Y: ");
            
            /* Read that value and store into valueY */
            scanf("%d", &valueY);
            printf("From child: Reading Y from the user\n");
            
            /* print statement about reading X from pipe, and writing Y to pipe */
            printf("From child: Reading X from the pipe\n");
            printf("From child: Writing Y into the pipe\n");
            
            /* Print out the integer child recieved from pipe */
            printf("From child: The value of X is %d\n", valX);
            
            /* Try to write Y into the pipe, if failed, exit */
            if (write(fd2[1], &valueY, sizeof(valueY)) < 0){
                perror("From child: Failed to write response value");
                exit(1);
            }
        }
        
        /* exit process to represent success */
        exit(0);
    }

    /* Else pid = 0, so we're in the child */
    else{

        /* Print the PID for child 1 */
        printf("\nFrom parent process %d: child with PID %d is created\n", getpid(), pid);
        
        /* Ask the user for a value for X */
        printf("From parent process %d: Please enter a value for X: ", getpid());
        
        /* Save user input as valueX */
        scanf("%d", &valueX);
        printf("From parent process %d: Reading X from the user\n", getpid());
        
        /* Write X into the pipe */
        printf("From parent process %d: Writing X into the pipe\n", getpid());
        
        /* Try writing X into the pipe, if failed exit */
        if (write(fd[1], &valueX, sizeof(valueX)) != sizeof(valueX)){
            perror("From parent process: Failed to send value to child");
            exit(1);
        }
        
        /* Create an int to store what we read from the pipe */
        int valY = 0;
        
        /* Read from the pipe */
        length = read(fd2[0], &valY, sizeof(valY));
        printf("\nFrom parent process %d: Reading Y from the pipe\n", getpid());
        
        /* If the length is < 0, then error */
        if (length < 0){
            perror("From parent process: Failed to read value from pipe");
            exit(1);
        }
        
        /* If the pipe is empty, then we've read EOF */
        else if (length == 0){
            fprintf(stderr, "From parent process: Read EOF from pipe");
        }
        
        /* If we got something from the pipe, then print out the value */
        else{
            printf("From parent process %d: The value of Y is %d\n", getpid(), valY);
        }
        
        /* Wait for process to terminate */
        wait(NULL);
    }
    
    /* Finish by returning 0 */
    return 0;
}
