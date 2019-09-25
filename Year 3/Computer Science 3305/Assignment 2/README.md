# Assignment 2

## Program Goals
• Get hands-on experience with the CPU scheduling algorithms
• Gain more experience with the C programming language from an OS’s CPU scheduling perspective

## Part 1: CPU Scheduling Environment Initialization

Your C program will perform the following tasks based on the given input file mullevel_queue_CPU_scheduling_input_file.txt:
1. Create the number of ready queues as stated in the given input file
2. Assign the priority level for each of the ready queues (as per the input file spec)
3. Assign each ready queue with a specific CPU scheduling algorithm (as per the input file spec, such as FCFS, SJF, RR etc.)
4. Assign time quantum for (as per input file spec) for RR algorithm
5. Create all the processes for each of the ready queues based on the input file specification (such as CPU burst time, arrival order etc.)

## Part 2: Scheduling Algorithm Execution

Your C program will perform the following tasks in order based on the given input file:
1. CPU scheduler will execute the top most priority queue
2. CPU scheduler will execute the second priority queue
3. CPU scheduler will execute the third priority queue
