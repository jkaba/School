# A provided makefile for CS4481 assignment02
 
# The makefile format
#target-name: target dependencies
#{-tab-}actions

#==================================================
# MACRO definitions
CFLAG = -std=c99 -Wall
CC = gcc

#==================================================
# All Targets
all: pgm_huffman_encode pgm_huffman_decode compare_pgm_images

#--------------------------------------------------
#Q8: Executable pgm_huffman_encode depends on 
#the source file pgm_huffman_encode.c and 
#the object files
#  generate_pixel_frequency.o
#  generate_huffman_nodes.o 
#  huffman_encode_image.o 
#  store_huffman_encoded_data.o 
#  libpnm.o
Q8 pgm_huffman_encode: pgm_huffman_encode.c \
                      generate_pixel_frequency.o \
                      generate_huffman_nodes.o \
                      huffman_encode_image.o \
                      store_huffman_encoded_data.o \
                      libpnm.o
	$(CC) $(CFLAG) -o pgm_huffman_encode \
                  pgm_huffman_encode.c \
                  generate_pixel_frequency.o \
                  generate_huffman_nodes.o \
                  huffman_encode_image.o \
                  store_huffman_encoded_data.o \
                  libpnm.o


#--------------------------------------------------
#Q9: Executable pgm_huffman_decode depends on 
#the source file pgm_huffman_decode.c and 
#the object files
#  read_huffman_encoded_data.o 
#  huffman_decode_image.o
#  libpnm.o
Q9 pgm_huffman_decode: pgm_huffman_decode.c \
                      read_huffman_encoded_data.o \
                      huffman_decode_image.o \
                      libpnm.o
	$(CC) $(CFLAG) -o pgm_huffman_decode \
                  pgm_huffman_decode.c \
                  read_huffman_encoded_data.o \
                  huffman_decode_image.o \
                  libpnm.o


#--------------------------------------------------
#Q10: Executable compare_pgm_images depends on 
#the source file compare_pgm_images.c and 
#the object files
#  mean_absolute_error.o
#  libpnm.o
Q10 compare_pgm_images: compare_pgm_images.c \
                        mean_absolute_error.o \
                        libpnm.o
	$(CC) $(CFLAG) -o compare_pgm_images \
                      compare_pgm_images.c \
                      mean_absolute_error.o \
                      libpnm.o


#--------------------------------------------------
#Q1: generate_pixel_frequency.o depends on 
#the source file 
#  generate_pixel_frequency.c 
#the header files 
#  generate_pixel_frequency.h
#  libpnm.h
Q1 generate_pixel_frequency.o: generate_pixel_frequency.c \
                               generate_pixel_frequency.h \
                               libpnm.h
	$(CC) $(CFLAG) -c generate_pixel_frequency.c


#--------------------------------------------------
#Q2: generate_huffman_nodes.o depends on 
#the source file 
#  generate_huffman_nodes.c 
#the header file
#  generate_huffman_nodes.h
Q2 generate_huffman_nodes.o: generate_huffman_nodes.c \
                             generate_pixel_frequency.h 
	$(CC) $(CFLAG) -c generate_huffman_nodes.c


#--------------------------------------------------
#Q3: huffman_encode_image.o depends on 
#the source file 
#  huffman_encode_image.c 
#the header files 
#  huffman_encode_image.h
#  libpnm.h
Q3 huffman_encode_image.o: huffman_encode_image.c \
                           huffman_encode_image.h \
                           libpnm.h
	$(CC) $(CFLAG) -c huffman_encode_image.c


#--------------------------------------------------
#Q4: store_huffman_encoded_data.o depends on 
#the source file 
#  store_huffman_encoded_data.c 
#the header files 
#  store_huffman_encoded_data.h
#  libpnm.h
Q4 store_huffman_encoded_data.o: store_huffman_encoded_data.c \
                                 store_huffman_encoded_data.h \
                                 libpnm.h
	$(CC) $(CFLAG) -c store_huffman_encoded_data.c


#--------------------------------------------------
#Q5: read_huffman_encoded_data.o depends on 
#the source file 
#  read_huffman_encoded_data.c 
#the header file
#  read_huffman_encoded_data.h
Q5 read_huffman_encoded_data.o: read_huffman_encoded_data.c \
                                read_huffman_encoded_data.h 
	$(CC) $(CFLAG) -c read_huffman_encoded_data.c


#--------------------------------------------------
#Q6: huffman_decode_image.o depends on 
#the source file 
#  huffman_decode_image.c 
#the header files 
#  huffman_decode_image.h
#  libpnm.h
Q6 huffman_decode_image.o: huffman_decode_image.c \
                           huffman_decode_image.h \
                           libpnm.h
	$(CC) $(CFLAG) -c huffman_decode_image.c


#--------------------------------------------------
#Q7: mean_absolute_error.o depends on 
#the source file 
#  mean_absolute_error.c 
#the header files 
#  mean_absolute_error.h
#  libpnm.h
Q7 mean_absolute_error.o: mean_absolute_error.c \
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
 
testEncoderValidation: pgm_huffman_encode 
#
# checking inputs validation for pgm_huffman_encode
#
	@echo "----------------------------------------"
	@echo "Checking inputs validation for pgm_huffman_encode"
	@echo
	./pgm_huffman_encode 
	@echo "----------------------------------------"
	./pgm_huffman_encode tttt 
	@echo "----------------------------------------"
	./pgm_huffman_encode test_square.raw.pgm 
	@echo "----------------------------------------"
	./pgm_huffman_encode smooth.raw.pgm      smooth.comp  tttt
	@echo "----------------------------------------"

testDecoderValidation: pgm_huffman_decode 
#
# checking inputs validation for pgm_huffman_decode
#
	@echo "----------------------------------------"
	@echo "Checking inputs validation for pgm_huffman_decode"
	@echo
	./pgm_huffman_decode 
	@echo "----------------------------------------"
	./pgm_huffman_decode tttt 
	@echo "----------------------------------------"
	./pgm_huffman_decode test_square.comp
	@echo "----------------------------------------"
	./pgm_huffman_decode test_square.raw.pgm 
	@echo "----------------------------------------"
	./pgm_huffman_decode smooth.comp         smooth.decomp.pgm  tttt
	@echo "----------------------------------------"

testCompareValidation: compare_pgm_images
#
# checking inputs validation for pgm_huffman_encode
#
	@echo "----------------------------------------"
	@echo "Checking inputs validation for pgm_huffman_encode"
	@echo
	./compare_pgm_images
	@echo "----------------------------------------"
	./compare_pgm_images tttt 
	@echo "----------------------------------------"
	./compare_pgm_images test_square.raw.pgm 
	@echo "----------------------------------------"
	./compare_pgm_images smooth.raw.pgm      smooth.decomp.pgm  tttt
	@echo "----------------------------------------"

testValidation: pgm_huffman_encode pgm_huffman_decode compare_pgm_images
	make testEncoderValidation
	make testDecoderValidation
	make testCompareValidation

#............................................................

testCompression: pgm_huffman_encode 
#
# Generating Huffman compressed images
#
	@echo "----------------------------------------"
	@echo "Generating  Huffman compressed images"
	@echo 
	./pgm_huffman_encode test_square.raw.pgm test_square.comp
	ls -l                test_square.raw.pgm test_square.comp
	@echo "----------------------------------------"
	./pgm_huffman_encode rectangle_2.raw.pgm rectangle.comp
	ls -l                rectangle_2.raw.pgm rectangle.comp
	@echo "----------------------------------------"
	./pgm_huffman_encode boats.raw.pgm       boats.comp
	ls -l                boats.raw.pgm       boats.comp
	@echo "----------------------------------------"
	./pgm_huffman_encode smooth.raw.pgm      smooth.comp
	ls -l                smooth.raw.pgm      smooth.comp
	@echo "----------------------------------------"

testDecompression: pgm_huffman_decode
#
# Generating Huffman decompressed images
#
	@echo "----------------------------------------"
	./pgm_huffman_decode test_square.comp    test_square.decomp.pgm
	@echo "----------------------------------------"
	./pgm_huffman_decode rectangle.comp      rectangle.decomp.pgm
	@echo "----------------------------------------"
	./pgm_huffman_decode boats.comp          boats.decomp.pgm
	@echo "----------------------------------------"
	./pgm_huffman_decode smooth.comp         smooth.decomp.pgm
	@echo "----------------------------------------"

testComparingImages: compare_pgm_images
#
# Comparing images
#
	@echo "----------------------------------------"
	./compare_pgm_images test_square.raw.pgm test_square.decomp.pgm
	@echo "----------------------------------------"
	./compare_pgm_images rectangle_2.raw.pgm rectangle.decomp.pgm
	@echo "----------------------------------------"
	./compare_pgm_images boats.raw.pgm       boats.decomp.pgm
	@echo "----------------------------------------"
	./compare_pgm_images smooth.raw.pgm      smooth.decomp.pgm
	@echo "----------------------------------------"

testAll: 
#
# All testing cases
#
	make testCompression
	make testDecompression
	make testComparingImages

#==================================================
#Clean all objected files and the executable file
clean:
	rm -f *.o
	rm -f  pgm_huffman_encode  pgm_huffman_decode compare_pgm_images


#Clean all compressed images
cleanCOMPRESSED:
	rm -f *.comp

#Clean all decompressed images
cleanDECOMPRESSED:
	rm -f *.decomp.pgm

#Clean compressed/decompressed files, object files, and executable file 
cleanAll:
	make clean
	make cleanCOMPRESSED cleanDECOMPRESSED
#==================================================
