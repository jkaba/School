# Assignment 3

## Description
We have seen how to send data over a TCP connection and now we want to explore data transfer using UDP. As you recall from the lectures, UDP is a non-reliable protocol so we are going to need to create a reliable transfer protocol in the application layer.

## Summary
We will once again have two applications (UDP_Client.py and UDP_Server.py) but this time we will be using the UDP protocol, not TCP to communicate across the network. This means we have to create the reliable data transfer protocol (rdt) we saw in our textbook, specifically, we will create rdt2.2 for this assignment.

## UDP Client
This app must connect to the UDP_Server app via UDP (you can use the local loopback address of 127.0.0.1 along with any port number you wish) then send three separate packets containing the following information:
NCC-1701 NCC-1664 NCC-1017

## UDP Server
This app will establish a UDP socket and listen for incoming connections from the client. When a connection is made the server will consume the data and follow the rdt2.2 process as shown in chapter 3 of the course textbook.
