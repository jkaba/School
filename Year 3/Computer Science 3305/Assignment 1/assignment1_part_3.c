/*
 Name: Jameel Kaba
 UWO id: jkaba
 Student #: 250796017
 
 CS3305B Assignment 1
 Part 3: I/O Redirection
 This program allows the shell command "ls -l | grep xxxx" to run.
 This is done with a parent calling ls -l and a child calling grep xxxx

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

int main(void){
    
	/* initialize variables */
	int fd[2];
	int n;
	char c;
	pid_t pid;
	int status;
    
	/* Creating pipe */
	if (pipe(fd) < 0){
		perror("fatal error");
		exit(1);
	}
    
	/* Calling fork / creating child */
	pid = fork();
    
	/* If pid is < 0, then there is an error  */
	if (pid < 0) {
		perror("fork error");
		exit(-1);
	}
        
	/* If pid is > 0, then we are in the parent */
	if(pid > 0){

		/* Close 1 end of the pipe */
		close(fd[0]);
        
		/* Try dup to redirect output */
		if (dup2(fd[1], STDOUT_FILENO) < 0){
            
		/* If failed, then error */
		perror("can't dup");
		exit(1);
		}
        
		/* Run ls -l */
		status = execlp("ls","ls","-l", NULL);
	        
		/* If status < 0, exec problem error */
		if (status < 0){
			perror("parent: exec problem");
			exit(1);
		}
        
		/* Wait for process to terminate */
		wait(NULL);
	}

	/* If pid = 0, then we are in the child */
	else{
        
		/* close 1 end of the pipe */
		close(fd[1]);
        
		/* Try dup to redirect input */
		if (dup2(fd[0], STDIN_FILENO) < 0){
            
			/* If failed, then error */
			perror("can't dup");
			exit(1);
		}

		/* Run grep xxxx */
		status = execlp("grep","grep", "xxxx", NULL);
        
		/* If status < 0, then exec problem error */
		if (status < 0){
			perror("parent: exec problem");
			exit(1);            
		}
	}
    
	/* Finish by returning 0 */
	return 0;
}
