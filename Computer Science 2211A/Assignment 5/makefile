#format is target-name: target dependencies
#{-tab-}actions

# MACRO definitions
CC  = gcc
CFLAG = -std=c99 -Wall

# All Targets
all: operation

#Executable operation depends on the files operation.o operation_functions.o
operation: operation.o operation_functions.o
	$(CC) $(CFLAG) -o operation operation.o operation_functions.o

# operation.o depends on the source and header files
operation.o: operation.c operation_functions.h
	$(CC) $(CFLAG) -c operation.c

# operation_functions.o depends on the source and header files
operation_functions.o: operation_functions.c operation_functions.h
	$(CC) $(CFLAG) -c operation_functions.c

# test cases
test: operation
	operation 1 2 3 4
	operation 1 0 2 0
	operation 0 3 0 8
	operation 4 0 0 5
	operation 0 5 4 0
	operation 0 0 1 2
	operation 1 2 0 0

#Clean the build directory
clean:
	rm -f *.o operation
