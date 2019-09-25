"""
Jameel Kaba (jkaba) 250796017
CS3357A Assignment 2
"""

#Import statement
import socket

#IP address and Port number
TCP_IP = '192.168.80.128'
TCP_PORT = 5005

#Create a socket and try to connect to the server
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSocket.connect((TCP_IP, TCP_PORT))

#When connection is established print the following
print ("Connection to Server Established")

#Have the user input a request to the server
request = raw_input('Input a request: ')

#Send the request
clientSocket.send(request)

#Recieve the response
modRequest = clientSocket.recv(1024)

#Print the response on Screen
print 'From Server: ', modRequest

#Close connection
clientSocket.close()
