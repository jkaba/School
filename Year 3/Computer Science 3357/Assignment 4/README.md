# Assignment 2

## Description

In Assignment #3 we implemented the rdt 2.2 protocol from the course textbook which allowed us to use UDP for relaible data transfers. Unfortunately, rdt 2.2 only accounted for corrupt packets so we will need to build on our code from Assignment #3 and add a timer to account for lost packets.
Summary

We will once again have two applications (UDP_Client.py and UDP_Server.py) using the UDP protocol to communicate across a network that can corrupt or lose data packets. This means we have to create the reliable data transfer protocol (rdt 3.0) we saw in our textbook by adding a timer to our client application.

## UDP Client
This app must connect to the UDP_Server app via UDP (127.0.0.1 but please choose any port number you wish) then send three separate packets containing the following information:
NCC-1701
NCC-1664
NCC-1017
When adding the timer to the Client.py application, the timeout value should be set to 9ms

## UDP Server
This app will establish a UDP socket and listen for incoming connections from the client. When a connection is made the server will consume the data and follow the rdt 2.2 process as shown in chapter 3 of the course textbook.
