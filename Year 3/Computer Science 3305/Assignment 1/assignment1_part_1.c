/*
 Name: Jameel Kaba
 UWO ID: jkaba
 Student #: 250796017
 
 CS3305B Assignment 1
 Part 1: Parent and Child processes
 This program has a parent that creates 3 children
 Child 1 creates a child 1.1
 The parent waits for child 2 to finish before making child 3
 Child 3 exits to an external program
 */


/* include statements */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(){

	/* initialize variables */
	pid_t pid;
	pid_t parent;
    
	/* First fork */
	pid = fork();
    
	/* If the pid is < 0, then there is an error */
	if (pid < 0){
		perror("fork()");
		printf("main function: errno number is %d\n",errno);
		exit(pid);
	}
    
	/* If pid is > 0, then this is the parent process */
	if (pid > 0){
  
		/* Print out that child 1 is created, and what the PID is */
		printf("From parent process %d: child_1 is created with PID %d\n", getpid(), pid);
        
		/* Save the current pid value into parent */
		parent = getpid();
        
		/* Wait for process to terminate */
		wait(NULL);
        
		/* Create child 2 */
		pid = fork();
        
		/* If the pid is 0, then we are in child 2 */
		if(pid == 0){
            
			/* Print out, what the PID for child 2 is */
			printf("From parent process %d: child_2 is created with PID %d\n", getppid(), getpid());
			printf("From parent process %d: Waiting for child_2 to complete before creating child_3\n", getppid());
		}
        
		/* Wait for process to terminate */
		wait(NULL);
        
		/* If the current pid, is that of the parents then continue */
		if(parent == getpid()){
            
			/* Create child 3 */
			pid = fork();
            
			/* If the pid is 0, then we are in child 3 */
			if(pid == 0){
                
				/* Print out, what the PID for child 3 is */
				printf("From parent process %d: child_3 is created with PID %d\n", getppid(), getpid());
                
				/* Print out, child 3 calling the external program */
				printf("From child_3: Calling an external program B and leaving child_3...\n");
                
				/* Leave the program, and run the external program */
				execl("./B", "./B", (char*) NULL);
                
				/* If there was a problem, return -1 as there is an issue */
				return -1;
			}
		}
        
		/* Wait for process to terminate */
		wait(NULL);
	}
    
	/* If pid is 0, then we are in child 1 */
	else{
        
		/* Create child 1.1 */
		pid = fork();
        
		/* If pid is 0, we are in child 1.1 */
		if(pid == 0){
            
		/* Print out, what the PID for child 1.1 is */
		printf("From child_1: child_1.1 is created with PID %d\n", getpid());
		}
	}
    
	/* Return 0, to finish */
	return 0;
}
