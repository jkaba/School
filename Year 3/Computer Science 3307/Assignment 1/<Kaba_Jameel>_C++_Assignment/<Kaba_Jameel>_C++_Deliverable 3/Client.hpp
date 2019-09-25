//
//  Client.hpp
//  CS3307A Assignment 1
//  Jameel Kaba (jkaba) 250796017
//

// Define Statements
#ifndef Client_hpp
#define Client_hpp

// Include Statements
#include <string>
#include "Account.hpp"

// Using std for I/O
using namespace std;

// Client class used to create a new client
class Client{
    
// Protected variables
protected:
    
    // User ID
    string id;
    
    // User Pin
    string pwd;
    
    // Chequing Account
    Account chqAcc;
    
    // Savings Account
    Account savAcc;
    
// Public Variables
public:
    
    // General Constructor
    Client();
    
    // Specific Constructor
    Client(string, string);
    
    // Deconstructor
    ~Client();
    
    // Get ID
    string getId();
    
    // Get Pin
    string getPwd();
    
    // Get Chequing Account
    Account getChq();
    
    // Get Savings Account
    Account getSav();
    
    // Set Chequing Account
    void setChq(Account);
    
    // Set Savings Account
    void setSav(Account);
    
    // Set User ID
    void setId(string);
    
    // Set Pin
    void setPwd(string);
    
    // Deposit into Chequing Account
    void depChq(float);
    
    // Deposit into Savings Account
    void depSav(float);
    
    // Withdraw from Chequing Account
    void withChq(float);
    
    // Withdraw from Savings Account
    void withSav(float);
};

#endif /* Client_hpp */
