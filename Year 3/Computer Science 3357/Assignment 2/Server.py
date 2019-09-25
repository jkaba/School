"""
Jameel Kaba (jkaba) 250796017
CS3357A Assignment 2
"""

#Import statements
import socket
import time

#IP address and Port location
TCP_IP = '192.168.80.128'
TCP_PORT = 5005

#Create socket
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket.bind((TCP_IP, TCP_PORT))
serverSocket.listen(1)

#Print statement to notify that server is running
print('The Server is ready to recieve')

#While loop that allows the server to keep running after a connection is closed
while 1:
    
	#Connection Socket represents the client
	connectionSocket, addr = serverSocket.accept()
    
	#Recieve the request from the client
	request = connectionSocket.recv(1024)
    
	#If the client asks the following question then return the appropriate results
	if request == "What is the current date and time?":
		retRequest = "Current Date and Time - " + time.strftime("%d/%m/%y") + " " + time.strftime("%H:%M:%S")
		connectionSocket.send(retRequest)
    
	#Else send an error message back
	else:
		retRequest = "Error 404: Request Failed"
		connectionSocket.send(retRequest)

	#Close the connection to the client
	connectionSocket.close()
