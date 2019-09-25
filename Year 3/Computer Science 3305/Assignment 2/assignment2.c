/*
 CS3305B Assignment 2
 Name: Jameel Kaba
 GAUL/UWO ID: jkaba
 Student #: 250796017
 
 This program runs a Multilevel Queue CPU scheduling algorithm
 */

/* Include Statements */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/* Defining a variable for Size */
#define SIZE 10

/*
 The Ready Queue structure
 Each Ready Queue has the following
 - priority level
 - an array of burst time values
 - an array of wait time values
 - an array of processes
 - a timeQuantum value (0 if not round robin)
 - and a string for algorithm
 */
struct readyQueue{
    int priority;
    int burstTime[SIZE];
    int waitTime[SIZE];
    int processes[SIZE];
    int timeQuantum;
    char algorithm[30];
};

/*
 initialize method used to initialize the ready queue
 input: pointer to an integer representing the priority
 output: a constructed ready queue
 */
struct readyQueue initialize(int *priority){
    
    /* initialize variables */
    int i = 0;
    struct readyQueue inputQueue;
    
    /* for loop to set up process and wait time array */
    for(i = 0; i < SIZE; i++){
        inputQueue.processes[i] = i+1;
        inputQueue.waitTime[i] = 0;
    }
    
    /* Setting up the burst time array */
    int burstTimes[] = {10, 5, 7, 20, 17, 9, 3, 11, 15, 1};
    
    for (i = 0; i < SIZE; i++){
        inputQueue.burstTime[i] = burstTimes[i];
    }
    
    /* Set the priority to be what was passed as input */
    inputQueue.priority = *priority;
    
    
    /* Based on the priority level assign an algorithm, and a time quantam if necessary */
    char *algo[] = {"sjf", "fcfs", "rr"};
    
    if(*priority == 1){
        strcpy(inputQueue.algorithm, algo[0]);
        inputQueue.timeQuantum = 0;
    }
    
    else if(*priority == 2){
        strcpy(inputQueue.algorithm, algo[1]);
        inputQueue.timeQuantum = 0;
    }
    
    else{
        strcpy(inputQueue.algorithm, algo[2]);
        inputQueue.timeQuantum = 5;
    }
    
    /* Return an initialized ready queue */
    return inputQueue;
}

/*
 roundRobin method
 input: A pointer to a ready queue, a pointer to total time, and a pointer to a file
 
 Performs round robin scheduling for the ready queue, provided as input.
 */
void roundRobin(struct readyQueue *queue, int *totalTime, FILE *fp){
    
    /* Initialize variables */
    int i = 0;
    int j = 0;
    int turnaroundTime = 0;
    int proc = 0;
    int bursts = 0;
    int flag = SIZE;
    
    /* Print to output and to a file */
    printf("\nReady Queue priority: %d", queue->priority);
    fprintf(fp, "\nReady Queue priority: %d", queue->priority);
    printf("\nReady Queue using Round Robin Scheduling\n\n");
    fprintf(fp, "\nReady Queue using Round Robin Scheduling\n\n");
    printf("Process Number\t\tBurst Time Remaining\t\tTurnaround Time\n");
    fprintf(fp, "Process Number\t\tBurst Time Remaining\t\tTurnaround Time\n");
    
    /* While loop that performs the round robin */
    /* While i is not equal to SIZE */
    while(i != flag){
        
        /* If the burst time at position i is 0, then increment i */
        if(queue->burstTime[i] == 0){
            i++;
        }
        
        else{
            
            /* Subtract the time quantum from the burst time, and add to turnaround time */
            queue->burstTime[i] -= queue->timeQuantum;
            turnaroundTime += queue->timeQuantum;
            
            /* If the burst time is now < 0 or = 0 */
            if(queue->burstTime[i] < 0 || queue->burstTime[i] == 0){
                
                /* Calculate turnaround time, set burst time to 0, and print */
                turnaroundTime += queue->burstTime[i];
                queue->burstTime[i] = 0;
                printf("Process #%d\t\tFinished\t\t\t%d\n", queue->processes[i], turnaroundTime);
                fprintf(fp, "Process #%d\t\tFinished\t\t\t%d\n", queue->processes[i], turnaroundTime);
            }
            
            /* If the burst time is > 0 then print out the burst time */
            else{
                printf("Process #%d\t\t%d\n", queue->processes[i], queue->burstTime[i]);
                fprintf(fp, "Process #%d\t\t%d\n", queue->processes[i], queue->burstTime[i]);
            }
            
            /* Dequeue and Enqueue from ready queue */
            if(queue->burstTime[i] > 0){
                
                /* Save process and burst time at i into a variable */
                proc = queue->processes[i];
                bursts = queue->burstTime[i];
                
                /* Shift the elements forward 1 */
                for(j = 0; j < SIZE-1; j++){
                    queue->processes[j] = queue->processes[j+1];
                    queue->burstTime[j] = queue->burstTime[j+1];
                }
                
                /* Enqueue/place the original element i at the end of the queue */
                queue->processes[j] = proc;
                queue->burstTime[j] = bursts;
            }
        }
    }
    
    /* Calculate total time */
    *totalTime += turnaroundTime;
}

/*
 firstComeFirstServe method
 input: A pointer to a ready queue, a pointer to total time, and a pointer to a file
 
 Performs first come first serve scheduling for the ready queue provided as input.
 */
void firstComeFirstServe(struct readyQueue *queue, int *totalTime, FILE *fp){
    
    /* Initialize variables */
    int i;
    int j;
    int totalWaitTime = 0;
    
    /* Print to output and to file */
    printf("\nReady Queue priority: %d", queue->priority);
    fprintf(fp, "\nReady Queue priority: %d", queue->priority);
    printf("\nReady Queue using First Come First Serve Scheduling\n\n");
    fprintf(fp, "\nReady Queue using First Come First Serve Scheduling\n\n");
    
    /* Calculate the wait time for each element, total wait time, and the total time needed for the method */
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < i; j++){
            queue->waitTime[i] += queue->burstTime[j];
        }
        totalWaitTime += queue->waitTime[i];
        *totalTime += queue->burstTime[i];
        
    }
    
    /* Calculate the average waiting time */
    float avgWait = totalWaitTime/(float)SIZE;
    
    /* FCFS scheduling, print out the results to output and to file */
    printf("Process Number\t\tBurst Time\t\tWait Time\n");
    fprintf(fp, "Process Number\t\tBurst Time\t\tWait Time\n");
    
    for(i = 0; i < SIZE; i++){
        printf("Process #%d\t\t%d\t\t\t%d\n", queue->processes[i], queue->burstTime[i], queue->waitTime[i]);
        fprintf(fp, "Process #%d\t\t%d\t\t\t%d\n", queue->processes[i], queue->burstTime[i], queue->waitTime[i]);
    }
    
    /* Print out the average waiting time */
    printf("\nAverage Waiting Time: %g ms\n", avgWait);
    fprintf(fp, "\nAverage Waiting Time: %g ms\n", avgWait);
}

/*
 shortestJobFirst method
 input: A pointer to a ready queue, a pointer to total time, and a pointer to a file
 
 Performs shortest job first scheduling for the ready queue provided as input.
 */
void shortestJobFirst(struct readyQueue *queue, int *totalTime, FILE *fp){
    
    /* Initialize variables */
    int i = 0;
    int j = i + 1;
    int totalWaitTime = 0;
    int tempBurst = 0;
    int tempProc = 0;
    int position = 0;
    
    /* Print to output and to file */
    printf("\nReady Queue priority: %d", queue->priority);
    fprintf(fp, "\nReady Queue priority: %d", queue->priority);
    printf("\nReady Queue using Shortest Job First Scheduling\n\n");
    fprintf(fp, "\nReady Queue using Shortest Job First Scheduling\n\n");
    
    /* Sort the queue so that process arranged from smallest to biggest via burst time */
    for(i = 0; i < SIZE; i++){
        position = i;
        
        /* If the burst time at j is less that burst time at i, set position to j */
        for(j = i + 1; j < SIZE; j++)
        {
            if(queue->burstTime[j] < queue->burstTime[position]){
                position = j;
            }
        }
        
        /* Swap the burst time at i with the burst time at position */
        tempBurst = queue->burstTime[i];
        queue->burstTime[i] = queue->burstTime[position];
        queue->burstTime[position] = tempBurst;
        
        /* Swap the process id at i with the process id at position */
        tempProc = queue->processes[i];
        queue->processes[i] = queue->processes[position];
        queue->processes[position] = tempProc;
    }
    
    /* Calculate the wait time for each element, total wait time, and the total time needed for the method */
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < i; j++){
            queue->waitTime[i] += queue->burstTime[j];
        }
        totalWaitTime += queue->waitTime[i];
        *totalTime += queue->burstTime[i];
    }
    
    /* Calculate the average wait time */
    float avgWait = totalWaitTime/(float)SIZE;
    
    /* SJF scheduling, print out the results to output and to file */
    printf("Process Number\t\tBurst Time\t\tWait Times\n");
    fprintf(fp, "Process Number\t\tBurst Time\t\tWait Times\n");
    
    for(i = 0; i < SIZE; i++){
        printf("Process #%d\t\t%d\t\t\t%d\n", queue->processes[i], queue->burstTime[i], queue->waitTime[i]);
        fprintf(fp, "Process #%d\t\t%d\t\t\t%d\n", queue->processes[i], queue->burstTime[i], queue->waitTime[i]);
    }
    
    /* Print out the average waiting time */
    printf("\nAverage Waiting Time: %g ms\n", avgWait);
    fprintf(fp, "\nAverage Waiting Time: %g ms\n", avgWait);
}

/* Main Method */
int main(int argc, char* argv[]){
    
    /* Initialize variables */
    int totalTime = 0;
    int time1 = 0;
    int time2 = 0;
    int time3 = 0;
    int i = 0;
    FILE *fp;
    
    /* Open/Create the text file to be written to */
    fp = fopen("multilevel_cpu_output.txt", "w+");
    
    /* Initialize Ready Queue 1 with priority 2 */
    int priority = 2;
    struct readyQueue queue1 = initialize(&priority);
    
    /* Initialize Ready Queue 2 with priority 3 */
    priority = 3;
    struct readyQueue queue2 = initialize(&priority);
    
    /* Initialize Ready Queue 3 with priority 1 */
    priority = 1;
    struct readyQueue queue3 = initialize(&priority);
    
    /* Store the ready queues into an array, placed by highest priority to lowest priority */
    struct readyQueue order[3];
    order[0] = queue2;
    order[1] = queue1;
    order[2] = queue3;
    
    /* for loop that loops through the array, running the appropriate algorithm */
    for(i = 0; i < 3; i++){
        
        /* If the algorithm is rr, then run round robin scheduling on that queue */
        if(strcmp(order[i].algorithm, "rr") == 0){
            roundRobin(&order[i], &time1, fp);
        }
        
        /* If the algorithm is fcfs, then run first come first serve scheduling on that queue */
        if(strcmp(order[i].algorithm, "fcfs") == 0){
            firstComeFirstServe(&order[i], &time2, fp);
        }
        
        /* If the algorithm is sjf, then run shortest job first scheduling on that queue */
        if(strcmp(order[i].algorithm, "sjf") == 0){
            shortestJobFirst(&order[i], &time3, fp);
        }
    }
    
    /* Calculate and print out the total time needed */
    totalTime = time1 + time2 + time3;
    printf("\nTotal time taken: %d ms\n", totalTime);
    fprintf(fp, "\nTotal time taken: %d ms\n", totalTime);
    
    /* Return 0 to finish the program */
    return 0;
    
}
