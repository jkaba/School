//
//  Account.cpp
//  CS3307A Assignment 1
//  Jameel Kaba (jkaba) 250796017
//

// Include statements
#include "Account.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Using std for I/O
using namespace std;

// Initializing variables
float balance;
bool initialized;
string type;
vector<string> transHist;

// Constructors

// General Constructor
Account::Account(){
    initialized = false;
}

// Specific Constructor
Account::Account(float bal, string t){
    balance = bal;
    type = t;
    initialized = true;
}

// Deconstructor
Account::~Account(void){
    
}


// METHODS

/*
 getBal method that get's the
 balance of an account
 */
float Account::getBal(){
    return balance;
}
/*
 getIni method used to determine
 wether or not an account is initialized
 */
bool Account::getIni(){
    return initialized;
}

/*
 deposit method that add's the input float value
 to the account currently in use
 */
void Account::deposit(float amount){
    
    // calculate the new balance
    balance = balance + amount;
    ostringstream hist;
    
    // print out a deposit method; also displays new balance
    hist << "Deposit of $" << amount << ". Current balance: $" << balance;
    transHist.push_back(hist.str());
}

/*
 withdraw method used to subtract/withdraw the input float
 value from the account currently in use
 */
void Account::withdraw(float amount){
    
    // Calculate new balance
    balance = balance - amount;
    ostringstream hist;
    
    // If the chequing account has a balance under 1000
    if (type == "Chq" && balance < 1000) {
        
        // Provide a message stating the withdrawn amount + $2 surcharge + the new balance
        hist << "Withdraw of $" << amount << " ($2 surcharge included). Current balance: $" << balance;
        transHist.push_back(hist.str());
    }
    
    // Else print out the withdrawn amount and new balance
    else {
        hist << "Withdraw of $" << amount << ". Current balance: $" << balance;
        transHist.push_back(hist.str());
    }
}

/*
 history method that prints out the transaction history
 */
void Account::history(){
    cout << endl;
    for (int i = 0; i < transHist.size(); i++){
        cout << transHist[i] << endl;
    }
};
