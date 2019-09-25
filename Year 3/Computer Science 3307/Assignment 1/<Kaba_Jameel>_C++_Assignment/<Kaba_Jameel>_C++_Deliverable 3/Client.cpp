//
//  Client.cpp
//  CS3307A Assignment 1
//  Jameel Kaba (jkaba) 250796017
//

// Include Statements
#include "Client.hpp"
#include <iostream>
#include <string>

// Using std for I/O
using namespace std;

// Initialize Variables
string id;
string pwd;
Account chqAcc;
Account savAcc;

// General Constructor
Client::Client() {
}


// Specific Constructor
Client::Client(string id, string pwd) {
    this->id = id;
    this->pwd = pwd;
}

// Deconstructor
Client::~Client(void){
}

/*
 Get ID method that returns a client id
 */
string Client::getId() {
    return id;
}

/*
 Get Pwd method that returns a client's pin
 */
string Client::getPwd() {
    return pwd;
}

/*
 Get Chequing Account method that returns
 a client's chequing account
 */
Account Client::getChq(){
    return chqAcc;
}

/*
 Get Savings Account method that returns 
 a client's Savings account
 */
Account Client::getSav(){
    return savAcc;
}

/*
 Set Chequing account method that sets
 a client's chequing account to the one
 provided as input
 */
void Client::setChq(Account newChq){
    chqAcc = newChq;
}

/*
 Set Savings Account method that sets 
 a client's savings account to the one
 provided as input
 */
void Client::setSav(Account newSav){
    savAcc = newSav;
}

/*
 Set Id method that sets a client's id
 to the one specified as input
 */
void Client::setId(string newId){
    id = newId;
}

/*
 Set pwd method that sets a client's pin
 to the one specified as input
 */
void Client::setPwd(string newPwd){
    pwd = newPwd;
}

/*
 Deposit Chequing method that deposits
 a specified amount into the client's 
 chequing account
 */
void Client::depChq(float amount){
    chqAcc.deposit(amount);
}

/*
 Deposit Savings method that deposits
 a specified amount into the client's 
 savings account
 */
void Client::depSav(float amount){
    savAcc.deposit(amount);
}

/*
 Withdraw Chequing method that withdraws
 a specified amount from the client's 
 chequing account
 */
void Client::withChq(float amount){
    return chqAcc.withdraw(amount);
}

/*
 Withdraw Savings method that withdraws
 a specified amount from the client's 
 savings account
 */
void Client::withSav(float amount){
    return savAcc.withdraw(amount);
}
