# A provided makefile for CS4481 assignment04
 
# The makefile format
#target-name: target dependencies
#{-tab-}actions

#==================================================
# MACRO definitions
CFLAG = -std=c99 -Wall
CC = gcc
LIBS = -lm

#==================================================
# All Targets

all All ALL: DPCM_encoding DPCM_decoding compare_pgm_images

#--------------------------------------------------
#Q3a: Executable DPCM_encoding depends on 
#the source file DPCM_encoding.c and 
#the object files
#  DPCM_encoding.o
#  DPCM_encoding_function.o
#  libpnm.o
Q3a DPCM_encoding: DPCM_encoding.c \
                      DPCM_encoding_function.o \
                      libpnm.o
	$(CC) $(CFLAG) -o DPCM_encoding \
                  DPCM_encoding.c \
                  DPCM_encoding_function.o \
                  libpnm.o $(LIBS)


#--------------------------------------------------
#Q3b: Executable DPCM_decoding depends on 
#the source file DPCM_decoding.c and 
#the object files
#  DPCM_decoding.o
#  DPCM_decoding_function.o
#  libpnm.o
Q3b DPCM_decoding: DPCM_decoding.c \
                      DPCM_decoding_function.o \
                      libpnm.o
	$(CC) $(CFLAG) -o DPCM_decoding \
                  DPCM_decoding.c \
                  DPCM_decoding_function.o \
                  libpnm.o $(LIBS)


#--------------------------------------------------
#Q3c: Executable compare_pgm_images depends on 
#the source file compare_pgm_images.c and 
#the object files
#  mean_absolute_error.o
#  libpnm.o
Q3c compare_pgm_images: compare_pgm_images.c \
                        mean_absolute_error.o \
                        libpnm.o
	$(CC) $(CFLAG) -o compare_pgm_images \
                      compare_pgm_images.c \
                      mean_absolute_error.o \
                      libpnm.o $(LIBS)


#--------------------------------------------------
#Q1: DPCM_encoding_function.o depends on 
#the source file 
#  DPCM_encoding_function.c 
#the header files 
#  DPCM_encoding_function.h
#  libpnm.h
Q1 DPCM_encoding_function.o: DPCM_encoding_function.c \
                               DPCM_encoding_function.h \
                               libpnm.h
	$(CC) $(CFLAG) -c DPCM_encoding_function.c


#--------------------------------------------------
#Q2: DPCM_decoding_function.o depends on 
#the source file 
#  DPCM_decoding_function.c 
#the header files 
#  DPCM_decoding_function.h
#  libpnm.h
Q2 DPCM_decoding_function.o: DPCM_decoding_function.c \
                               DPCM_decoding_function.h \
                               libpnm.h
	$(CC) $(CFLAG) -c DPCM_decoding_function.c


#--------------------------------------------------
#mean_absolute_error.o depends on 
#the source file 
#  mean_absolute_error.c 
#the header files 
#  mean_absolute_error.h
#  libpnm.h
mean_absolute_error.o: mean_absolute_error.c \
                               mean_absolute_error.h \
                               libpnm.h
	$(CC) $(CFLAG) -c mean_absolute_error.c


#--------------------------------------------------
#libpnm.o depends on 
#the source file 
#  libpnm.c 
#the header file 
#  libpnm.h
libpnm.o: libpnm.c libpnm.h
	$(CC) $(CFLAG) -c libpnm.c

#==================================================
# test cases
 
testEncoderValidation: DPCM_encoding 
#
# checking inputs validation for DPCM_encoding
#
	@echo "----------------------------------------"
	@echo "Checking inputs validation for DPCM_encoding"
	@echo
	./DPCM_encoding 
	@echo "----------------------------------------"
	./DPCM_encoding tttt 
	@echo "----------------------------------------"
	./DPCM_encoding test_square.raw.pgm 
	@echo "----------------------------------------"
	./DPCM_encoding smooth.raw.pgm   smooth.comp  tttt
	@echo "----------------------------------------"

testDecoderValidation: DPCM_decoding 
#
# checking inputs validation for DPCM_decoding
#
	@echo "----------------------------------------"
	@echo "Checking inputs validation for DPCM_decoding"
	@echo
	./DPCM_decoding
	@echo "----------------------------------------"
	./DPCM_decoding tttt 
	@echo "----------------------------------------"
	./DPCM_decoding test_square.comp
	@echo "----------------------------------------"
	./DPCM_decoding test_square.raw.pgm 
	@echo "----------------------------------------"
	./DPCM_decoding smooth.comp  smooth.decomp.pgm  tttt
	@echo "----------------------------------------"

testCompareValidation: compare_pgm_images
#
# checking inputs validation for compare_pgm_images
#
	@echo "----------------------------------------"
	@echo "Checking inputs validation for compare_pgm_images"
	@echo
	./compare_pgm_images
	@echo "----------------------------------------"
	./compare_pgm_images tttt 
	@echo "----------------------------------------"
	./compare_pgm_images test_square.raw.pgm 
	@echo "----------------------------------------"
	./compare_pgm_images smooth.raw.pgm  smooth.decomp.pgm  tttt
	@echo "----------------------------------------"

testValidation: DPCM_encoding DPCM_decoding compare_pgm_images
	make testEncoderValidation
	make testDecoderValidation
	make testCompareValidation

#............................................................

testCompression: DPCM_encoding
#
# Generating DPCM compressed images
#
	@echo "----------------------------------------"
	@echo "Generating  DPCM compressed images"
	@echo 
	./DPCM_encoding peppers.raw.pgm 1
	@echo "----------------------------------------"
	./DPCM_encoding peppers.raw.pgm 2
	@echo "----------------------------------------"
	./DPCM_encoding peppers.raw.pgm 3
	@echo "----------------------------------------"
	./DPCM_encoding peppers.raw.pgm 4
	@echo "----------------------------------------"
	./DPCM_encoding goldhill.raw.pgm 1
	@echo "----------------------------------------"
	./DPCM_encoding goldhill.raw.pgm 2
	@echo "----------------------------------------"
	./DPCM_encoding goldhill.raw.pgm 3
	@echo "----------------------------------------"
	./DPCM_encoding goldhill.raw.pgm 4
	@echo "----------------------------------------"
	
testDecompression: DPCM_decoding
#
# Generating DPCM compressed images
#
	@echo "----------------------------------------"
	@echo "Generating  DPCM compressed images"
	@echo 
	./DPCM_decoding peppers.raw.pgm.1.DPCM
	@echo "----------------------------------------"
	./DPCM_decoding peppers.raw.pgm.2.DPCM
	@echo "----------------------------------------"
	./DPCM_decoding peppers.raw.pgm.3.DPCM
	@echo "----------------------------------------"
	./DPCM_decoding peppers.raw.pgm.4.DPCM
	@echo "----------------------------------------"
	./DPCM_decoding goldhill.raw.pgm.1.DPCM
	@echo "----------------------------------------"
	./DPCM_decoding goldhill.raw.pgm.2.DPCM
	@echo "----------------------------------------"
	./DPCM_decoding goldhill.raw.pgm.3.DPCM
	@echo "----------------------------------------"
	./DPCM_decoding goldhill.raw.pgm.4.DPCM
	@echo "----------------------------------------"

testComparingImages: compare_pgm_images
#
# Comparing images
#
	@echo "----------------------------------------"
	./compare_pgm_images peppers.raw.pgm peppers.raw.pgm.1.DPCM.pgm
	@echo "----------------------------------------"
	./compare_pgm_images peppers.raw.pgm peppers.raw.pgm.2.DPCM.pgm
	@echo "----------------------------------------"
	./compare_pgm_images peppers.raw.pgm peppers.raw.pgm.3.DPCM.pgm
	@echo "----------------------------------------"
	./compare_pgm_images peppers.raw.pgm peppers.raw.pgm.4.DPCM.pgm
	@echo "----------------------------------------"
	./compare_pgm_images goldhill.raw.pgm goldhill.raw.pgm.1.DPCM.pgm
	@echo "----------------------------------------"
	./compare_pgm_images goldhill.raw.pgm goldhill.raw.pgm.2.DPCM.pgm
	@echo "----------------------------------------"
	./compare_pgm_images goldhill.raw.pgm goldhill.raw.pgm.3.DPCM.pgm
	@echo "----------------------------------------"
	./compare_pgm_images goldhill.raw.pgm goldhill.raw.pgm.4.DPCM.pgm
	@echo "----------------------------------------"

testAll TestAll  testALL TestALL  testall Testall: #
# All testing cases
#
	make testCompression
	make testDecompression
	make testComparingImages

#==================================================
#Clean all objected files and the executable file
clean  Clean CLEAN:
	rm -f *.o
	rm -f  DPCM_encoding DPCM_decoding compare_pgm_images


#Clean all compressed images
cleanCOMPRESSED:
	rm -f *.DPCM
	rm -f *.errors.csv

#Clean all decompressed images
cleanDECOMPRESSED:
	rm -f *.DPCM.pgm

#Clean compressed/decompressed files, object files, and executable file 
cleanAll CleanAll  cleanALL CleanALL cleanall Cleanall:
	make clean
	make cleanCOMPRESSED cleanDECOMPRESSED
#==================================================
