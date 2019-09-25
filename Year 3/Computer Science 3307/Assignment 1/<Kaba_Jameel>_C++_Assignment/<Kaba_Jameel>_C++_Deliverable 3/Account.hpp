//
//  Account.hpp
//  CS3307A Assignment 1
//  Jameel Kaba (jkaba) 250796017
//

// Define statements
#ifndef Account_hpp
#define Account_hpp

// Include statements
#include <string>
#include <sstream>
#include <vector>

// Using std for I/O
using namespace std;

// Account Class used for creating a new bank account
class Account{
    
// Protected variables
protected:
    
    // account balance
    float balance;
    
    // account initialization
    bool initialized;
    
    // account type
    string type;
    
    // account transaction history
    vector<string> transHist;
    
// public methods
public:
    
    // Standard constructor
    Account();
    
    // Specific constructor
    Account(float, string);
    
    // Deconstructor
    ~Account();
    
    // Get Balance
    float getBal();
    
    // Get Initialized
    bool getIni();
    
    // Add Balance
    void deposit(float);
    
    // Get Time
    string getTime();
    
    // Subtract Balance
    void withdraw(float);
    
    // Transaction History
    void history();
};

#endif /* Account_hpp */
