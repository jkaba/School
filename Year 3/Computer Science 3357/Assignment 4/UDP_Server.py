#CS3357A Assignment 4
#Name: Jameel Kaba 
#GAUL/UWO ID: jkaba
#Student #: 250796017

#UDP_Server.py representing the server in a UDP transfer using rdt 2.2
#This program is meant to be run using python3

#import statements
import binascii
import socket
import struct
import sys
import hashlib

#Setting up the ip, port, and unpacker
UDP_IP = "127.0.0.1"
UDP_PORT = 5005
unpacker = struct.Struct('I I 8s 32s')

#Create the socket and listen
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
    
    #Receive Data
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    UDP_Packet = unpacker.unpack(data)
    
    #Print out where the message was sent from and what it says
    print("received from:", addr)
    print("received message:", UDP_Packet)
    
    #Create the Checksum for comparison
    values = (UDP_Packet[0],UDP_Packet[1],UDP_Packet[2])
    packer = struct.Struct('I I 8s')
    packed_data = packer.pack(*values)
    chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")
   
    #Compare Checksums to test for corrupt data
    if UDP_Packet[3] == chksum:
        
        #Print OK message
        print('CheckSums Match, Packet OK')
        
        #Create CheckSum for Acknowledgement
        values = (1,UDP_Packet[1])
        UDP_Data = struct.Struct('I I')
        packed_data = UDP_Data.pack(*values)
        chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")
        
        #Create the Acknowledgement packet
        values2 = (1,UDP_Packet[1], chksum)
        UDP_Packet_Data = struct.Struct('I I 32s')
        UDP_Packet = UDP_Packet_Data.pack(*values2)
        
        #Print out what's being sent and send Acknowledgement
        print("Sending message:", values2, "\n")
        sock.sendto(UDP_Packet, addr)

    #Packet is corrupt
    else:
        
        #Print error message
        print('Checksums Do Not Match, Packet Corrupt')

        #Send error packet
        #Create CheckSum for error
        
        #Set the sequence to opposite of what it should be
        if UDP_Packet[1] == 0:
            values = (1, 1)
        else:
            values = (1, 0)

        UDP_Data = struct.Struct('I I')
        packed_data = UDP_Data.pack(*values)
        chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")
        
        #Create the error packet
        #Set the sequence to opposite of what it should be
        if UDP_Packet[1] == 0:
            values2 = (1, 1, chksum)
        else:
            values2 = (1, 0, chksum)

        UDP_Packet_Data = struct.Struct('I I 32s')
        UDP_Packet = UDP_Packet_Data.pack(*values2)

        #Print out what's being sent and send error
        print("Sending message:", values2, "\n")
        sock.sendto(UDP_Packet, addr)


