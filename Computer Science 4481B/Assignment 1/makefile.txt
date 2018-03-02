# A provided makefile for CS4481 assignment01
 
# The makefile format
#target-name: target dependencies
#{-tab-}actions

#==================================================
# MACRO definitions
CC = gcc
CFLAG = -std=c99 -Wall

#==================================================
# All Targets
all: main

#Executable main depends on the files main.o libpnm.o
main: main.o libpnm.o
	$(CC) $(CLAG) main.o libpnm.o -o main

#main.o depends on the source file main.c and the header file libpnm.h
main.o: main.c libpnm.h
	$(CC) $(CLAG) -c main.c

#libpnm.o depends on the source file libpnm.c and the header file libpnm.h
libpnm.o: libpnm.c libpnm.h
	$(CC) $(CLAG) -c libpnm.c

#==================================================
# test cases
#
testValidation: 
#
# checking inputs validation
#
	@echo "----------------------------------------"
	@echo "Checking inputs validation"
	@echo 
	main 1 120 120 
	@echo "----------------------------------------"
	main 0 120 120 image 0 
	@echo "----------------------------------------"
	main 4 120 120 image 0 
	@echo "----------------------------------------"
	main 1 125 120 image 1 
	@echo "----------------------------------------"
	main 1  -4 120 image 1 
	@echo "----------------------------------------"
	main 3 124 120 image 1 
	@echo "----------------------------------------"
	main 3  -4 120 image 1 
	@echo "----------------------------------------"
	main 1 120  -6 image 1 
	@echo "----------------------------------------"
	main 1 120 120 image 2 
	@echo "----------------------------------------"

testPBM: 
#
# Generating PBM images
#
	@echo "----------------------------------------"
	@echo "Generating PBM images"
	@echo 
	main 1 120 120 binary_120_120_raw.pbm 1 
	@echo "----------------------------------------"
	main 1 120 120 binary_120_120_ascii.pbm 0 
	@echo "----------------------------------------"
	main 1 1200 1200 binary_1200_1200_ascii.pbm 0 
	@echo "----------------------------------------"
	main 1 1200 300 binary_1200_300_ascii.pbm 0 
	@echo "----------------------------------------"
	main 1 300 1200 binary_300_1200_ascii.pbm 0 
	@echo "----------------------------------------"
	main 1 4 120 binary_4_120_ascii.pbm 0 
	@echo "----------------------------------------"

testPGM: 
#
# Generating PGM images
#
	@echo "----------------------------------------"
	@echo "Generating PGM images"
	@echo 
	main 2 120 120 gray_120_120_raw.pgm 1 
	@echo "----------------------------------------"
	main 2 120 120 gray_120_120_ascii.pgm 0 
	@echo "----------------------------------------"
	main 2 1200 1200 gray_1200_1200_ascii.pgm 0 
	@echo "----------------------------------------"
	main 2 1200 300 gray_1200_300_ascii.pgm 0 
	@echo "----------------------------------------"
	main 2 300 1200 gray_300_1200_ascii.pgm 0 
	@echo "----------------------------------------"
	main 2 4 120 gray_4_120_ascii.pgm 0 
	@echo "----------------------------------------"

testPPM: 
#
# Generating PPM images
#
	@echo "----------------------------------------"
	@echo "Generating PPM images"
	@echo 
	main 3 120 120 color_120_120_raw.ppm 1 
	@echo "----------------------------------------"
	main 3 120 120 color_120_120_ascii.ppm 0 
	@echo "----------------------------------------"
	main 3 1200 1200 color_1200_1200_ascii.ppm 0 
	@echo "----------------------------------------"
	main 3 1200 300 color_1200_300_ascii.ppm 0 
	@echo "----------------------------------------"
	main 3 300 1200 color_300_1200_ascii.ppm 0 
	@echo "----------------------------------------"
	main 3 6 120 color_4_120_ascii.ppm 0 
	@echo "----------------------------------------"

testAll: 
#
# All testing cases
#
	make testValidation
	make testPBM
	make testPGM
	make testPPM

#==================================================
#Clean all objected files and the executable file
clean:
	rm -f *.o
	rm -f main

#Clean all PBM images
cleanPBM:
	rm -f *.pbm

#Clean all PGM images
cleanPGM:
	rm -f *.pgm

#Clean all PPM images
cleanPPM:
	rm -f *.ppm

#Clean all pnm images
cleanPNM:
	make cleanPBM
	make cleanPGM
	make cleanPPM

#Clean pnm files, object files, and executable file 
cleanAll:
	make clean
	make cleanPNM
#==================================================
