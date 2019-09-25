# Assignment 2

## Description

In this assignment you will create a networked date/time server and a client to access the server.

The basic interaction between the client and server should be as follows:
Server establishes connection and listens for incoming client requests.
Client connects to server and sends ASCII request “What is the current date and time?” Server responds with “Current Date and Time – 09/29/2016 09:00:01”
Client closes connection, server stays running listening for next connection

## Part A: Developing Applications
Server
- Only required to handle one client interaction at a time
- Can listen on any IP & port you choose
- Must respond to invalid requests with an error message
- Valid request is “What is the current date and time?”
- Response to valid request must be in the format: “Current Date and Time – MM/DD/YYYY hh:mm:ss”

Client
- Allows user to enter text commands to be sent to the server
- Displays response back from server.

## Part B - "Sniff" Request / Response between Server and Client
Use Wireshark to capture traffic between client and server.
