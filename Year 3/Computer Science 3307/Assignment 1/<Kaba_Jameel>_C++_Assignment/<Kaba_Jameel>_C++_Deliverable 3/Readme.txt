CS3307A Assignment 1
Readme 

Name: Jameel Kaba
GAUL ID: jkaba
Student #: 250796017

This program was written on a Mac using the Xcode IDE
This program is intended to be run on a Mac.

This read me file is to provide instructions as to how to compile the banking assignment

Ensure that the directory contains the following files
- main.cpp
- Account.cpp
- Account.hpp
- Client.cpp
- Client.hpp
- bank

bank is the executable file to be run on a Mac
* If you are going to follow the command line instructions, then a new bank file will be made *

Using Xcode
- Create a new Xcode project
- Transfer all the files in this directory into the project
- Build the project (There shouldn’t be any issues)
- Run the project and enjoy

Note: When using Xcode, the trace.txt and client.txt files are located in the debug folder

Command Line instructions:
- To create the executable file open up a command line prompt
- Change into the directory containing the cpp files
- Enter the following: g++ main.cpp Client.cpp Account.cpp -o bank

This will create an executable file known as bank, which can be opened and run on a mac.

Note: When using command line, the trace.txt and client.txt files are located in the main/home directory 
