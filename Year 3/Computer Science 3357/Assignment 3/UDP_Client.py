#CS3357A Assignment 3
# Jameel Kaba (250796017) jkaba

#UDP_Client.py representing the client in a UDP transfer using rdt 2.2
#This program is meant to be run using python3

#Import Statements
import binascii
import socket
import struct
import sys
import hashlib

#Setting up the ip, port, and unpacker
UDP_IP = "127.0.0.1"
UDP_PORT = 5005
unpacker = struct.Struct('I I 32s')

#Setting up check variables
check = True
count = 0
error = 0

#Print out the target ip and port
print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)

#Create the 1st Checksum
values = (0,0,b'NCC-1701')
UDP_Data = struct.Struct('I I 8s')
packed_data = UDP_Data.pack(*values)
chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")

#Create 2nd Checksum
values2 = (0,1,b'NCC-1664')
UDP_Data2 = struct.Struct('I I 8s')
packed_data2 = UDP_Data.pack(*values2)
chksum2 =  bytes(hashlib.md5(packed_data2).hexdigest(), encoding="UTF-8")

#Create 3rd Checksum
values3 = (0,0,b'NCC-1017')
UDP_Data3 = struct.Struct('I I 8s')
packed_data3 = UDP_Data.pack(*values3)
chksum3 =  bytes(hashlib.md5(packed_data3).hexdigest(), encoding="UTF-8")

#Build the 1st UDP Packet
values = (0,0,b'NCC-1701',chksum)
UDP_Packet_Data = struct.Struct('I I 8s 32s')
UDP_Packet = UDP_Packet_Data.pack(*values)

#Build 2nd UDP Packet
values2 = (0,1,b'NCC-1664',chksum2)
UDP_Packet_Data2 = struct.Struct('I I 8s 32s')
UDP_Packet2 = UDP_Packet_Data2.pack(*values2)

#Build 3rd UDP Packet
values3 = (0,0,b'NCC-1017',chksum3)
UDP_Packet_Data3 = struct.Struct('I I 8s 32s')
UDP_Packet3 = UDP_Packet_Data3.pack(*values3)

#Setting up the socket to send and recieve
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

#Display what's being sent and send it
print("Sending message:", values, "\n")
sock.sendto(UDP_Packet, (UDP_IP, UDP_PORT))

#While check is true, send and recieve packets
while check:

    #Recieve an acknowledgement from the server
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    UDP_Packet4 = unpacker.unpack(data)

    #Display the recieved message
    print("received from:", addr)
    print("received message:", UDP_Packet4)

    #Check the checksums to ensure the packet is not corrupted
    #Create the Checksum for comparison
    values = (UDP_Packet4[0],UDP_Packet4[1])
    packer = struct.Struct('I I')
    packed_data = packer.pack(*values)
    chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")

    #First Packet
    if count == 0:
        
        #Compare Checksums to test for comparison
        if(UDP_Packet4[2] == chksum):
            
            #Print OK message
            print('CheckSums Match, Packet OK')
            
            #Make sure that packet recieved is an acknowledgement
            if(UDP_Packet4[0] == 1):
                
                #Print OK message
                print('Packet Acknowledged')
                
                #Make sure the packet sequence is in the right order
                if(UDP_Packet4[1] == 0):
                    
                    #Increment the count
                    count = 1
                    
                    #Print OK message
                    print('Packet in correct sequence')
                
                    #Print send message
                    print("Sending message:", values2, "\n")
                    
                    #Send the next packet
                    sock.sendto(UDP_Packet2, (UDP_IP, UDP_PORT))
                
                #Packet not in correct sequence
                else:
                    
                    #Print error message, and set error to 1
                    print('Packet in incorrect sequence')
                    error = 1
        
            #Packet recieved is not an acknowledgement
            else:
                
                #Print error message, and set error to 1
                print('Packet Not Acknowledged')
                error = 1
    
        #Checksums don't match, packet is corrupt
        else:
            
            #Print error message, and set error to 1
            print('CheckSums do not Match, Packet Corrput')
            error = 1
            
    #Second Packet
    elif count == 1:
        
        #Compare the Checksums to test for comparison
        if(UDP_Packet4[2] == chksum):
            
            #Print OK message
            print('CheckSums Match, Packet OK')

            #Make sure that packet recieved is an acknowledgement
            if(UDP_Packet4[0] == 1):
                
                #Print OK message
                print('Packet Acknowledged')

                #Make sure that the packet is in the correct sequence
                if(UDP_Packet4[1] == 1):
                    
                    #Increment the count
                    count = 2
                    
                    #Print OK message
                    print('Packet in correct sequence')

                    #Print send message
                    print("Sending message:", values3, "\n")
                    
                    #Send the next packet
                    sock.sendto(UDP_Packet3, (UDP_IP, UDP_PORT))
                
                #Packet is not in the correct sequence
                else:
                    
                    #Print error message and set error to 2
                    print('Packet in incorrect sequence')
                    error = 2
        
            #Packet is not acknowledged
            else:
                
                #Print error message and set error to 2
                print('Packet Not Acknowledged')
                error = 2

        #Checksums don't match, packet is corrupt
        else:
            
            #Print error message and set error to 2
            print('CheckSums do not Match, Packet Corrput')
            error = 2

    #Third Packet
    elif count == 2:
        
        #Compare the Checksums to test for comparison
        if(UDP_Packet4[2] == chksum):
            
            #Print OK message
            print('CheckSums Match, Packet OK')

            #Make sure packet recieved is an acknowledgement
            if(UDP_Packet4[0] == 1):
                
                #Print OK message
                print('Packet Acknowledged')

                #Make sure packet is in correct sequence
                if(UDP_Packet4[1] == 0):
                    
                    #Increment count
                    count = 3
                    
                    #Print OK message
                    print('Packet in correct sequence\n')

                #Packet is not in correct sequence
                else:
                    
                    #Print error message and set error to 3
                    print('Packet in incorrect sequence')
                    error = 3
            
            #Packet is not an acknowledgement
            else:
                
                #Print error message and set error to 3
                print('Packet Not Acknowledged')
                error = 3
                    
        #CheckSums do not Match, packet is corrupt
        else:
            
            #Print error message and set error to 3
            print('CheckSums do not Match, Packet Corrput')
            error = 3

    #No more packets to send, end connection
    if count == 3:
        
        #Print exit message
        print("Connection Closed\n")
        
        #Set check to false to exit the loop
        check = False

    #If error is not 0 then there is a problem
    if error != 0:
        
        #Problem in packet 1
        if error == 1:
            
            #Print resend message and resend first packet
            print("Resending message:", values, "\n")
            sock.sendto(UDP_Packet, (UDP_IP, UDP_PORT))
            
            #Reset error to 0
            error = 0
    
        #Problem in packet 2
        elif error == 2:
            
            #Print resend message and resend second packet
            print("Resending message:", values2, "\n")
            sock.sendto(UDP_Packet2, (UDP_IP, UDP_PORT))
            
            #Reset error to 0
            error = 0
        
        #Problem in packet 3
        elif error == 3:
            
            #Print resend message and resend third packet
            print("Resending message:", values3, "\n")
            sock.sendto(UDP_Packet3, (UDP_IP, UDP_PORT))
            
            #Reset error to 0
            error = 0