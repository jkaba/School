//
//  main.cpp
//  CS3307A Assignment 1
//  Jameel Kaba (jkaba) 250796017
//

// Include Statements
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Client.hpp"
#include "Account.hpp"
#include <vector>
#include <iomanip>
#include <fstream>
#include <ctime>

// Using std for I/O
using namespace std;

// Initialize variables
float amt;
string userId;
string pin;
string option;
vector<Client> clientList;
bool trace;
ofstream traceFile;
ofstream clientFile;
ifstream myFile;
time_t now;
string currentTime;

// Initialize methods
void menu();
void signUp(int k);
void signIn();
void clientOptions(int i);
void transferToUser(int i, int user, string type);
void printInfo(int i);
void manager();
int withdrawCheck(int i, string type);
string getTime();

/*
 Client Exists method that determines wether a specific
 client exists; returns the position on the client list if
 the client exists, else returns -1
 */
int clientExists(string id){
    
    for (int i = 0; i < clientList.size(); i++){
        if (clientList[i].getId() == id)
            return i;
    }
    return -1;
}

/*
 Open Account method that takes an int and creates an account for the user based on the input
 */
int openAccount(int i){
    
    string type;
    float initBal;
    
    cout << "Are you opening a chequing or savings account?\n \n Enter:\n 0 for Chequing \n 1 for Savings\n x to Cancel" << "\n\n ";
    cin >> type;
    
    // if 'x' is entered then cancel the process and return 0
    if (type == "x"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " Canceled the account opening process.\n";
        }
        return 0;
    }
    
    // if '0' is entered then create a chequing account
    else if (type == "0"){
        
        // Check to see if a chequing account already exists
        if (clientList[i].getChq().getIni()){
            cout << "A chequing account already exists.\n";
            if (trace){
                traceFile << getTime() << " --- " << userId << " Attempted to open a chequing account but it already exists\n" ;
            }
            openAccount(i);
        }
        
        // If a chequing account doesn't exist then create one
        else {
            if (trace){
                traceFile << getTime() << " --- " << userId << " Opened a chequing account.\n";
            }
            
            // Enter the initial balance for the account
            cout << "\nEnter the initial balance for the account:\n\n ";
            cin >> initBal;
            clientList[i].setChq(Account(initBal, "Chq"));
            if (trace){
                traceFile << getTime() << " --- " << userId << " Entered $" << initBal << " as the chequing account's initial balance.\n";
            }
        }
    }
    
    // If '1' is entered then create a savings account
    else if (type == "1"){
        
        // Check to see if a savings account already exists
        if (clientList[i].getSav().getIni()){
            cout << "A savings account already exists.\n";
            if (trace){
                traceFile << getTime() << " --- " << userId << " Attempted to open a savings account but it already exists.\n";
            }
            openAccount(i);
        }
        
        // If a savings account doesn't exist then create one
        else {
            if (trace){
                traceFile << getTime() << " --- " << userId << " Opened a savings account.\n";
            }
            
            // Enter the initial balance for the savings account
            cout << "\nEnter the initial balance for the account:\n\n ";
            cin >> initBal;
            clientList[i].setSav(Account(initBal, "Sav"));
            if (trace){
                traceFile << getTime() << " --- " << userId << " Entered $" << initBal << " as the savings account's initial balance.\n";
            }
        }
    }
    
    // If something other than 'x', '0', '1' is entered return an error
    else {
        cout << "\nIncorrect response. Please try again. \n ";
        if (trace){
            traceFile << getTime() << " --- " << userId << " Entered an invalid input in the open account process.\n";
        }
        openAccount(i);
    }
    
    // Account creation complete
    cout << "\nYour account has been successfully opened.\n" << endl;
    return 1;
}

/*
 Close Account method that takes an int and closes an account for the user
 */
void closeAccount(int i){
    
    cout << "\nEnter:\n0 to close your chequing account\n1 to close your savings account\nx to cancel\n\n ";
    cin >> option;
    
    // If '0' is entered then try to close a chequing account
    if (option == "0"){
        if (clientList[i].getChq().getIni()){
            if (clientList[i].getSav().getIni()){
                
                // If Chequing Account balance is > 0 then fail to close account
                if (clientList[i].getChq().getBal() != 0){
                    cout << "\nChequing account still has money in it. Failed to close Chequing Account\n\n";
                    if (trace){
                        traceFile << getTime() << " --- " << userId << " Attempted to close the chequing account but could not as it still has money in it.\n";
                    }
                }
                
                // Else Close the chequing account
                else {
                    clientList[i].setChq(Account());
                    if (trace){
                        traceFile << getTime() << " --- " << userId << " Closed the chequing account.\n";
                    }
                    cout << "\nClosed Chequing account\n\n";
                }
            }
            
            // If the chequing account is the only account fail to close
            else {
                cout << "\nFailed to close chequing account as it is the only account.\n\n";
                if (trace){
                    traceFile << getTime() << " --- " << userId << " Attempted to close the chequing account but could not as it is the only account.\n";
                }
            }
        }
        
        // If the chequing account does not exist then operation fails
        else {
            if (trace){
                traceFile << getTime() << " --- " << userId << " Attempted to close a chequing account that does not exist.\n";
            }
            cout << "\nChequing account does not exist.\n\n";
        }
    }
    
    // If '1' is entered try to close a savings account
    else if (option == "1"){
        if (clientList[i].getSav().getIni()){
            if (clientList[i].getChq().getIni()){
                
                // If the savings account still has money then fail to close
                if (clientList[i].getSav().getBal() != 0){
                    cout << "\nSavings Account still has money in it. Failed to close Savings Account.\n\n";
                    if (trace){
                        traceFile << getTime() << " --- " << userId << " Attempted to close the savings account but could not as it still has money in it.\n";
                    }
                }
                
                // Else successfully close the savings account
                else {
                    clientList[i].setSav(Account());
                    cout << "\nClosed Savings account\n\n";
                    if (trace){
                        traceFile << getTime() << " --- " << userId << " Closed the savings account.\n";
                    }
                }
            }
            
            // If the savings account is the only account then fail to close
            else {
                cout << "\nFailed to close savings account because it is the only account.\n\n";
                if (trace){
                    traceFile << getTime() << " --- " << userId << " Attempted to close the savings account but could not as it is the only account.\n";
                }
            }
        }
        
        // If the account doesn't exist then fail to close
        else {
            cout << "\nSavings account does not exist.\n\n";
            if (trace){
                traceFile << getTime() << " --- " << userId << " Attempted to close a savings account that does not exist.\n";
            }
        }
    }
    
    // If 'x' is entered then cancel the operation
    else if (option == "x"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " Canceled the account closing process.\n";
        }
        if (clientList[i].getId() == "manager"){
            manager();
        }
        else {
            clientOptions(i);
        }
    }
    
    // If an invalid input then try again
    else {
        cout << "\nInvalid input\n";
        if (trace){
            traceFile << getTime() << " --- " << userId << " Entered an invalid input in the close account process.\n";
        }
        closeAccount(i);
    }
}

/*
 Deposit method that deposits an amount specified by the user into a specified account
 */
void deposit(int i){
    cout << "\nEnter:\n0 to deposit to your chequing account\n1 to deposit to your savings account\nx to cancel\n\n ";
    cin >> option;
    
    // If '0' is entered then deposit into chequing
    if (option == "0"){
        if (clientList[i].getChq().getIni()){
            if (trace){
                traceFile << getTime() << " --- " << userId << " Chose to deposit money into their chequing account.\n";
            }
            
            // Enter how much to deposit
            cout << "\n\nHow much would you like to deposit?\n";
            cin >> amt;
            clientList[i].depChq(amt);
            cout << "Deposit successful.\n\n";
            cout << "\nYour chequing account balance is now: $" << clientList[i].getChq().getBal() << "\n\n";
            if (trace){
                traceFile << getTime() << " --- " << userId << " Entered $" << amt << " and it was deposited into their chequing account.\n";
            }
        }
        
        // Don't deposit if chequing account doesn't exist
        else {
            if (trace){
                traceFile << getTime() << " --- " << userId << " Chose to deposit money into their chequing account, but it doesn't exist\n";
            }
            cout << "\nChequing account does not exist\n";
            deposit(i);
        }
    }
    
    // If '1' is entered then deposit into savings
    else if (option == "1"){
        if (clientList[i].getSav().getIni()){
            if (trace){
                traceFile << getTime() << " --- " << userId << " Chose to deposit money into their savings account.\n";
            }
            
            // Enter how much to deposit
            cout << "\n\nHow much would you like to deposit today?\n";
            cin >> amt;
            clientList[i].depSav(amt);
            cout << "Deposit successful.\n\n";
            cout << "\nYour savings account balance is now: $" << clientList[i].getSav().getBal() << "\n\n";
            if (trace){
                traceFile << getTime() << " --- " << userId << " Entered $" << amt << " and it was deposited into their savings account.\n";
            }
        }
        
        // Don't deposit if savings account doesn't exist
        else {
            if (trace){
                traceFile << getTime() << " --- " << userId << " Chose to deposit money into their savings account, but it doesn't exist\n";
            }
            cout << "\nSavings account does not exist\n";
            deposit(i);
        }
    }
    
    // If 'x' is entered then cancel the process
    else if (option == "x"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " Canceled the deposit process.\n";
        }
        clientOptions(i);
    }
    
    // Else if invalid input then try again
    else {
        if (trace){
            traceFile << getTime() << " --- " << userId << " entered an invalid input in the deposit process.\n";
        }
        cout << "\nInvalid input\n";
        closeAccount(i);
    }
}

/*
 Withdraw method that withdraws a specified amount from a user's account
 */
void withdraw(int i) {
    cout << "\nEnter:\n0 to withdraw from your chequing account\n1 to withdraw from your savings account\nx to cancel\n\n ";
    cin >> option;
    
    // If '0' is entered then withdraw from chequing
    if (option == "0"){
        if (clientList[i].getChq().getIni()){
            if (trace){
                traceFile << getTime() << " --- " << userId << " Withdrew money from their chequing account.\n";
            }
            
            // Enter the amount to withdraw
            cout << "\nHow much would you like to withdraw?\n\n";
            cin >> amt;
            if (trace){
                traceFile << getTime() << " --- " << userId << " Entered $" << amt << " for the amount to withdraw from their chequing account.\n";
            }
            withdrawCheck(i, "Chq");
            cout << "\nYour chequing account balance is now: $" << clientList[i].getChq().getBal() << "\n\n";
        }
        
        // If no chequing account exists then fail to withdraw
        else {
            if (trace){
                traceFile << getTime() << " --- " << userId << " Chose to withdraw money from their chequing account, but it doesn't exist.\n";
            }
            cout << "\nChequing account does not exist\n";
            withdraw(i);
        }
    }
    
    // If '1' is entered then withdraw from savings
    else if (option == "1"){
        if (clientList[i].getSav().getIni()){
            if (trace){
                traceFile << getTime() << " --- " << userId << " Withdrew money from their savings account.\n";
            }
            
            // Enter amount ot be withdrawn
            cout << "\nHow much would you like to withdraw today?\n";
            cin >> amt;
            if (trace){
                traceFile << getTime() << " --- " << userId << " entered $" << amt << " for the amount to withdraw from their savings account.\n";
            }
            withdrawCheck(i, "Sav");
            cout << "\nYour savings account balance is now: $" << clientList[i].getSav().getBal() << "\n\n";
        }
        
        // If no savings account exists, then fail to withdraw
        else {
            if (trace){
                traceFile << getTime() << " --- " << userId << " chose to withdraw money from their savings account, but it does not exist.\n";
            }
            cout << "\nSavings account does not exist\n";
            withdraw(i);
        }
    }
    
    // If 'x' is entered then cancel the operation
    else if (option == "x"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " canceled the withdraw process.\n";
        }
        clientOptions(i);
    }
    
    // Else invalid operation, try again
    else {
        if (trace){
            traceFile << getTime() << " --- " << userId << " entered an invalid input in the withdraw process.\n";
        }
        cout << "\nInvalid input\n";
        withdraw(i);
    }
}

/*
 Check Balance method that checks the balance in the user's chequing and savings accounts
 */
void checkBal(int i){
    if (clientList[i].getChq().getIni()){
        cout << "\nYour chequing account balance is : $" << clientList[i].getChq().getBal();
    }
    if (clientList[i].getSav().getIni()){
        cout << "\nYour savings account balance is : $" << clientList[i].getSav().getBal();
    }
    cout << "\n\n";
}

/*
 Transfer method that allows the user to transfer either to another one of their accounts
 or to a different user's acount
 */
void transfer(int i) {
    
    int user;
    userId = clientList[i].getId();
    cout << "\nEnter:\n0 to transfer from your chequing account to your savings account\n1 to transfer from your savings account to your chequing account\n" <<
    "2 to transfer from your chequing account to another user's account\n3 to transfer from your savings account to another user's account\nx to cancel\n\n ";
    cin >> option;
    
    // If '0' is chosen transfer from chequing to savings
    if (option == "0"){
        if (clientList[i].getChq().getIni() && clientList[i].getSav().getIni()){
            if (trace){
                traceFile << getTime() << " --- " << userId << " Chose to transfer from their chequing account to their savings account.\n";
            }
            
            // Input how much is being transfered
            cout << "\nHow much would you like to transfer?\n";
            cin >> amt;
            if (trace){
                traceFile << getTime() << " --- " << userId << " Entered $" << amt << " as the amount to transfer.\n";
            }
            
            // If there are enough funds then complete transfer
            if (withdrawCheck(i, "Chq") > 0){
                if (trace){
                    traceFile << getTime() << " --- " << userId << "'s transfer completed.\n";
                }
                clientList[i].depSav(amt);
                checkBal(i);
                clientOptions(i);
            }
            
            // Not enough funds == no transfer
            else {
                if (trace){
                    traceFile << getTime() << " --- " << userId << "'s transfer failed.\n";
                }
                transfer(i);
            }
        }
        
        // If the client doesn't have the other account, then transfer canceled
        else {
            if (trace){
                traceFile << getTime() << " --- " << userId << " wanted to transfer from their chequing account to their " <<
                "savings account but does not have both accounts. Transaction cancelled.\n";
            }
            cout << "\nYou're missing either a chequing or savings account. Transfer Failed\n";
            transfer(i);
        }
        
    }
    
    // If '1' is chosen transfer from savings to chequing
    else if (option == "1"){
        if (clientList[i].getChq().getIni() && clientList[i].getSav().getIni()){
            if (trace){
                traceFile << getTime() << " --- " << userId << " decided to transfer from their savings account to their chequing account.\n";
            }
            
            // Enter amount to be transfered
            cout << "\nHow much would you like to transfer?\n";
            cin >> amt;
            if (trace){
                traceFile << getTime() << " --- " << userId << " Entered $" << amt << " as the amount to transfer.\n";
            }
            
            // If there are enough funds then transfer success
            if (withdrawCheck(i, "Sav") > 0){
                if (trace){
                    traceFile << getTime() << " --- " << userId << "'s transfer complete.\n";
                }
                clientList[i].depChq(amt);
                checkBal(i);
                clientOptions(i);
            }
            
            // If there aren't enough funds then transfer failed
            else {
                if (trace){
                    traceFile << getTime() << " --- " << userId << "'s transfer failed.\n";
                }
                transfer(i);
            }
        }
        
        // If the user is missing an account transfer failed
        else {
            if (trace){
                traceFile << getTime() << " --- " << userId << " wanted to transfer from their savings account to their " <<
                "chequing account but does not have both accounts. Transaction cancelled.\n";
            }
            cout << "\nYou're missing either a chequing or savings account. Transfer Failed\n";
            transfer(i);
        }
    }
    
    // If '2' is selected then the user wants to transfer from chequing to another user's account
    else if (option == "2"){
        if (clientList[i].getChq().getIni()){
            if (trace){
                traceFile << getTime() << " --- " << userId << " decided to transfer from their chequing account to another user's account.\n";
            }
            
            // Enter the id of the recipient
            cout << "\nEnter the user ID you wish to transfer money to:\n";
            cin >> userId;
            user = clientExists(userId);
            
            // Check to make sure the user exists before transfering
            if (user > 0){
                if (trace){
                    traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user they will transfer money to.\n";
                }
                transferToUser(i, user, "chq");
            }
            
            // If the user doesn't exist then transfer failed
            else {
                if (trace){
                    traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user they will transfer money to, " <<
                    "but that user does not exist. Transaction cancelled.\n";
                }
                cout << "\nThat user does not exist\n";
                transfer(i);
            }
        }
        
        // If the user exists but the client doesn't have a chequing account; transaction fails
        else {
            if (trace){
                traceFile << getTime() << " --- " << userId << " wanted to transfer from their chequing account to another user's account, " <<
                "but they does not have a chequing account. Transaction cancelled.\n";
            }
            cout << "\nTransaction Failed. You need a chequing account\n";
            transfer(i);
        }
    }
    
    // If '3' is selected then transfer from savings to another user's account
    else if (option == "3"){
        if (clientList[i].getSav().getIni()){
            if (trace){
                traceFile << getTime() << " --- " << userId << " decided to transfer from their savings account to another user's account.\n";
            }
            
            // Enter the recipient's id
            cout << "\nEnter the user ID you wish to transfer money to:\n";
            cin >> userId;
            user = clientExists(userId);
            
            // If the user exists then transfer
            if (user > 0){
                if (trace){
                    traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user they will transfer money to.\n";
                }
                transferToUser(i, user, "sav");
            }
            
            // If the user doesn't exist then transfer fails
            else {
                if (trace){
                    traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user they will transfer money to, " <<
                    "but that user does not exist. Transaction cancelled.\n";
                }
                cout << "\nThat user does not exist\n";
                transfer(i);
            }
        }
        
        // If the client doesn't have a savings account then transfer fails
        else {
            if (trace){
                traceFile << getTime() << " --- " << userId << " wanted to transfer from their savings account to another user's account, " <<
                "but they does not have a savings account. Transaction cancelled.\n";
            }
            cout << "\nTransfer Failed. You need a savings account\n";
            transfer(i);
        }
    }
    
    // If 'x' is selected then cancel the process
    else if (option == "x"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " canceled the transfer process.\n";
        }
        clientOptions(i);
    }
    
    // If invalid input try again
    else {
        if (trace){
            traceFile << getTime() << " --- " << userId << " entered an invalid input in the transfer process.\n";
        }
        cout << "\nInvalid input\n";
        transfer(i);
    }
}

/*
 transferToUser method that allows a user to transfer funds to another users
 chequing or savings account
 */
void transferToUser(int i, int user, string type){
    cout << "\nEnter:\n0 to transfer to their chequing account\n1 to transfer to their savings account\nx to cancel\n\n ";
    cin >> option;
    
    // If 0 is selected, Transfer to the users chequing account
    if (option == "0"){
        
        // Make sure the user has a chequing account
        if (clientList[user].getChq().getIni()){
            if (trace){
                traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() << "'s chequing account.\n";
            }
            
            // Enter how much is being transfered
            cout << "\nHow much would you like to transfer?\n";
            cin >> amt;
            if (trace){
                traceFile << getTime() << " --- " << clientList[i].getId() << " enetered $" << amt << " as the amount to transfer.\n";
            }
            
            // Check to see if there is enough funds in your savings account to transfer
            if (type == "sav"){
                if (withdrawCheck(i, "Sav") > 0){
                    if (trace){
                        traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer complete.\n";
                    }
                    // Transfer the funds into the users chequing account
                    clientList[user].depChq(amt);
                    checkBal(i);
                    clientOptions(i);
                }
                
                // If not enough funds, then the transfer failed
                else {
                    if (trace){
                        traceFile << getTime() << " --- " << userId << "'s transfer failed.\n";
                    }
                    transferToUser(i, user, type);
                }
            }
            
            // Check to see if there is enough funds in your chequing account to transfer
            else {
                if (withdrawCheck(i, "Chq") > 0){
                    if (trace){
                        traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer complete.\n";
                    }
                    
                    // Transfer the funds into the users chequing account
                    clientList[user].depChq(amt);
                    checkBal(i);
                    clientOptions(i);
                }
                
                // If not enough funds, then the transfer failed
                else {
                    if (trace){
                        traceFile << getTime() << " --- " << userId << "'s transfer failed.\n";
                    }
                    transferToUser(i, user, type);
                }
            }
        }
        
        // User does not have a chequing account, transaction fails
        else {
            if (trace){
                traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() <<
                "'s chequing account, but they do not have a chequing account. Transaction cancelled\n";
            }
            cout << "\nThe user does not have a chequing account\n";
            transferToUser(i, user, type);
        }
    }
    
    // If 1 is selected, then transfer to the users savings account
    else if (option == "1"){
        
        // Make sure the user has a savings account
        if (clientList[user].getSav().getIni()){
            if (trace){
                traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() << "'s savings account.\n";
            }
            
            // Enter the amount to be sent
            cout << "\nHow much would you like to transfer?\n";
            cin >> amt;
            if (trace){
                traceFile << getTime() << " --- " << clientList[i].getId() << " enetered $" << amt << " as the amount to transfer.\n";
            }
            
            // Check to see if you have enough funds in savings to transfer
            if (type == "sav"){
                if (withdrawCheck(i, "Sav") > 0){
                    if (trace){
                        traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer complete.\n";
                    }
                    
                    // Transfer funds to the users savings account
                    clientList[user].depSav(amt);
                    checkBal(i);
                    clientOptions(i);
                }
                
                // Not enough funds, transfer fails
                else {
                    if (trace){
                        traceFile << getTime() << " --- " << userId << "'s transfer failed.\n";
                    }
                    transferToUser(i, user, type);
                }
            }
            
            // Check to see if you have enough funds in chequing to transfer
            else {
                if (withdrawCheck(i, "Chq") > 0){
                    if (trace){
                        traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer complete.\n";
                    }
                    
                    // Transfer the funds into the users savings account
                    clientList[user].depSav(amt);
                    checkBal(i);
                    clientOptions(i);
                }
                
                // Transfer failed, as not enough funds
                else {
                    if (trace){
                        traceFile << getTime() << " --- " << userId << "'s transfer failed.\n";
                    }
                    transferToUser(i, user, type);
                }
            }
        }
        
        // Else the user does not have a savings account
        else {
            if (trace){
                traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() <<
                "'s savings account, but they do not have a savings account. Transaction cancelled\n";
            }
            cout << "\nThe user does not have a savings account\n";
            transferToUser(i, user, type);
        }
    }
    
    // If x is chosen, then cancel the process
    else if (option == "x"){
        if (trace){
            traceFile << getTime() << " --- " << clientList[i].getId() << "decided to cancel the transfer to another user process.\n";
        }
        transfer(i);
    }
    
    // Invalid input try again
    else {
        if (trace){
            traceFile << getTime() << " --- " << clientList[i].getId() << " entered an invalid input in the transfer to another user process.\n";
        }
        cout << "\nInvalid input\n";
        transferToUser(i, user, type);
    }
}

/*
 withdrawCheck method that withdraws funds from a users account
 */
int withdrawCheck(int i, string type){
    float checkBal;
    
    // Get the balance from a user's chequing account
    if (type == "Chq"){
        checkBal = clientList[i].getChq().getBal();
    }
    
    // Get the balance from a user's savings account
    else {
        checkBal = clientList[i].getSav().getBal();
    }
    char ans;
    
    // If there are not enough funds to withdraw, send an error
    if ((checkBal - amt) < 0){
        cout << "\nThere is insufficient funds to process this transaction.\n Transaction Cancelled.\n" << endl;
        if (trace){
            traceFile << getTime() << " --- " << userId << "'s withdraw from their account failed because of insufficient funds.\n";
        }
        return 0;
    }
    
    // If the account is Chequing and the user will have less than $1000
    // Notify about the $2 surcharge, if not possible to pay then return error
    else if (type == "Chq"){
        if (checkBal - amt < 1000){
            if ((checkBal - amt - 2) < 0){
                cout << "\nCurrent withdraw subject to $2.00 Surcharge. Insufficient Funds.\n Transaction Failed.\n" << endl;
                if (trace){
                    traceFile << getTime() << " --- " << userId << "'s withdraw from their account failed because of insufficient funds (couldn't pay surcharge).\n";
                }
                return 0;
            }
            
            // If the user can pay the surcharge then continue
            else {
                cout << "\nYour balance after withdraw will be less than 1000 and subject to a $2.00 charge\nPress Y to continue or any other key to cancel request: Y/N?\n ";
                cin >> ans;
                
                // If Y/y is entered then confirm and complete transaction
                if (ans == 'Y' || ans == 'y'){
                    clientList[i].withChq(amt + 2);
                    cout << "Transaction successful. Thank you!\n" << endl;
                    if (trace){
                        traceFile << getTime() << " --- " << userId << " withdraw was subject to a $2.00 surcharge and (s)he agreed to pay it. Transaction was successful.\n";
                    }
                    return 1;
                }
                
                // If N/n was entered then cancel transaction
                else{
                    cout << "\nYour transaction has been cancelled. Surcharge was declined by customer.\n" << endl;
                    if (trace){
                        traceFile << getTime() << " --- " << userId << " withdraw was subject to a $2.00 surcharge and they declined to pay it. Transaction was cancelled.\n";
                    }
                    return 0;
                }
            }
        }
        
        // Withdraw from chequing normally
        else {
            clientList[i].withChq(amt);
            cout << "Transaction successful. Thank you!\n" << endl;
            if (trace){
                traceFile << getTime() << " --- " << userId << " withdraw from chequing account complete.\n";
            }
            return 1;
        }
    }
    
    // Withdraw from Savings
    else {
        clientList[i].withSav(amt);
        cout << "Transaction successful. Thank you!\n" << endl;
        if (trace){
            traceFile << getTime() << " --- " << userId << " withdraw from savings account complete.\n";
        }
        return 1;
    }
}

/*
 printInfo method that prints out a specific clients info
 */
void printInfo(int i){
    
    // Create a client based off the client in the list
    Client client = clientList[i];
    
    // Print out their info
    cout << "\nID: " << setw(15) << left << client.getId() << " Pin: " << client.getPwd();
    if (client.getChq().getIni()){
        cout << " Chequing: $" << client.getChq().getBal();
    }
    if (client.getSav().getIni()){
        cout << " Savings: $" << client.getSav().getBal();
    }
}

/*
 manager method that provides the menu options for the manager
 */
void manager() {
    cout << "\nEnter:\n0 to view the list of clients\n1 to view a client's information\n2 to view the information of all clientele\n3 to view total bank funds"
    << "\n4 to open an account\n5 to close an account\nx to logout\n\n ";
    cin >> option;
    
    // If 0 is entered then the manager wants to view the list of clients
    if (option == "0"){
        if (trace){
            traceFile << getTime() << " --- The manager decided to view the list of clients.\n";
        }
        cout << "\nList of clients:\n";
        for (int i = 2; i < clientList.size(); i++){
            cout << " " << clientList[i].getId() << endl;
        }
        manager();
    }
    
    // If 1 is entered the manager wants to view a specific clients info
    else if (option == "1"){
        if (trace){
            traceFile << getTime() << " --- The manager decided to view a clients information.\n";
        }
        
        // Enter the clients user id
        cout << "\nEnter the client's user ID: ";
        cin >> userId;
        int i = clientExists(userId);
        
        // If the client exists then print their info
        if (i > 0){
            if (trace){
                traceFile << getTime() << " --- The manager entered " << userId << " as the client to view.\n";
            }
            printInfo(i);
            cout << endl;
            manager();
        }
        
        // The client doesn't exist so return an error
        else {
            if (trace){
                traceFile << getTime() << " --- The manager entered " << userId << " as the client to view, but that client does not exist.\n";
            }
            cout << "\nThat client does not exist\n";
            manager();
        }
    }
    
    // If 2 is entered the manager wants to view the info for all clients
    else if (option == "2"){
        if (trace){
            traceFile << getTime() << " --- The manager decided to view the information of all clientele.\n";
        }
        
        // Print out all of the client info
        cout << "Clientele information:\n";
        for (int i = 2; i < clientList.size(); i++){
            printInfo(i);
        }
        cout << endl;
        manager();
    }
    
    // If 3 is entered, the manager wants to view the total bank funds
    else if (option == "3"){
        if (trace){
            traceFile << getTime() << " --- The manager decided to view the total bank funds.\n";
        }
        float savings = 0;
        float chequings = 0;
        
        // Calculate bank funds
        for (int i = 2; i < clientList.size(); i++){
            if (clientList[i].getChq().getIni()){
                chequings += clientList[i].getChq().getBal();
            }
            if (clientList[i].getSav().getIni()){
                savings += clientList[i].getSav().getBal();
            }
        }
        
        // Print out the bank funds
        cout << "\nTotal money in chequing: $" << chequings << "\nTotal money in savings: $" << savings << "\nTotal money: $" << chequings + savings << endl;
        manager();
    }
    
    // If 4 is chosen then the manager wants to open an account for a client
    else if (option == "4"){
        if (trace){
            traceFile << getTime() << " --- The manager decided to open an account for a user.\n";
        }
        
        // Check to see if the client exists
        cout << "\nEnter the client's user ID: ";
        cin >> userId;
        int i = clientExists(userId);
        
        // If the client exists then open an additional account
        if (i > 0){
            if (trace){
                traceFile << getTime() << " --- The manager entered " << userId << " as the client to open an account for.\n";
            }
            userId = "manager";
            openAccount(i);
            manager();
        }
        
        // The client is not a memeber of the bank, operation failed
        else {
            if (trace){
                traceFile << getTime() << " --- The manager entered " << userId << " as the new client to open an account for\n";
            }
            signUp(5);
            manager();
        }
    }
    
    // If 5 is selected, then the manager is closing an account for a user
    else if (option == "5"){
        if (trace){
            traceFile << getTime() << " --- The manager decided to close an account for a user.\n";
        }
        
        // Enter the client who will have an account closed
        cout << "\nEnter the client's user ID: ";
        cin >> userId;
        int i = clientExists(userId);
        
        // If the client exists then close the account
        if (i > 0){
            if (trace){
                traceFile << getTime() << " --- The manager entered " << userId << " as the client to close an account for.\n";
            }
            userId = "manager";
            closeAccount(i);
            manager();
        }
        
        // If the client doesn't exist then no account can be closed
        else {
            if (trace){
                traceFile << getTime() << " --- The manager entered " << userId << " as the client to close an account for, but that client does not exist.\n";
            }
            cout << "\nThat client does not exist\n";
            manager();
        }
    }
    
    // If x is entered then log out
    else if (option == "x"){
        if (trace){
            traceFile << getTime() << " --- The manager has logged out. \n\n";
        }
        menu();
    }
    
    // Invalid input try again
    else {
        if (trace){
            traceFile << getTime() << " --- The manager entered an invalid input in the option menu.\n";
        }
        cout << "\nInvalid input\n";
        manager();
    }
}

/*
 maint method that provides the menu for maintenance
 */
void maint() {
    cout << "\nEnter:\n0 to turn on the execution tracer\n1 to turn off the execution tracer\nx to logout\n\n ";
    cin >> option;
    
    // If 0 is selected, then turn on the execution trace
    if (option == "0"){
        
        // If the Execution trace is off, then on it
        if (!trace) {
            trace = true;
            cout << "\nExecution tracer has been turned on\n";
            traceFile.open("trace.txt", ios::app);
            traceFile << getTime() << " --- Maintenence man turned on execution tracer\n";
            maint();
        }
        
        // If execution trace is on then return an error
        else {
            cout << "\nExecution tracer already turned on\n";
            traceFile << getTime() << " --- Maintenence man attemped to turn execution tracer on, but it was already on\n";
            maint();
        }
    }
    
    // If 1 is entered, then off the tracer
    else if (option == "1"){
        
        // If tracer is on, then off it
        if (trace){
            trace = false;
            cout << "\nExecution tracer has been turned off\n";
            traceFile << getTime() << " --- Maintenence man turned off execution tracer\n\n";
            traceFile.close();
            maint();
        }
        
        // If tracer is off, then return an error
        else {
            cout << "\nExecution tracer already turned off\n";
            maint();
        }
    }
    
    // If x is entered, then log out
    else if (option == "x"){
        cout << endl;
        if (trace){
            traceFile << getTime() << " --- Maintenance man logged out.\n\n";
        }
        menu();
    }
    
    // Invalid input try again
    else {
        if (trace){
            traceFile << getTime() << " --- Maintenance man entered invalid input in the maintenance man option menu.\n";
        }
        cout << "\nInvalid input\n\n";
        maint();
    }
}

/*
 clientOptions method, the provides the menu for clients
 */
void clientOptions(int i){
    userId = clientList[i].getId();
    cout << "Enter:\n 0 to open a chequing or savings account\n 1 to close an account\n 2 to check balance\n 3 to deposit money\n"
    << " 4 to withdraw money \n 5 to transfer funds \n 6 to display transaction history\n x to logout\n\n ";
    cin >> option;
    
    // If 0 is entered, then the user wants to open up an additional account
    if (option == "0"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " has started the open account process.\n";
        }
        openAccount(i);
        clientOptions(i);
    }
    
    // If 1 is entered then the user wants to close an additional account
    else if (option == "1"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " has started the close account process.\n";
        }
        closeAccount(i);
        clientOptions(i);
    }
    
    // If 2 is entered then the user wants to check their balance
    else if (option == "2"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " has checked their account balances.\n";
        }
        checkBal(i);
        clientOptions(i);
    }
    
    // If 3 is entered then the user wants to deposit into an account
    else if (option == "3"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " has started the deposit process.\n";
        }
        deposit(i);
        clientOptions(i);
    }
    
    // If 4 is entered then the user wants to withdraw from an account
    else if (option == "4"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " has started the withdraw process.\n";
        }
        withdraw(i);
        clientOptions(i);
    }
    
    // If 5 is chosen then the user wants to transfer funds
    else if (option == "5"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " has started the transfer money process.\n";
        }
        transfer(i);
        clientOptions(i);
    }
    
    // If 6 is chosen then the user wants to display their transaction history
    else if (option == "6"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " has decided to display transaction history for their accounts.\n";
        }
        
        // Get the transaction history for chequing
        if (clientList[i].getChq().getIni()){
            cout << "\nTransaction history for chequing account:\n";
            clientList[i].getChq().history();
        }
        
        // Get the transaction history for savings
        if (clientList[i].getSav().getIni()){
            cout << "\nTransaction history for savings account:\n";
            clientList[i].getSav().history();
        }
        clientOptions(i);
    }
    
    // If x is entered, then log out
    else if (option == "x"){
        if (trace){
            traceFile << getTime() << " --- " << userId << " has logged out.\n\n";
        }
        menu();
    }
    
    // Invalid input, try again
    else {
        if (trace){
            traceFile << getTime() << " --- " << userId << " entered invalid input in the client option menu.\n";
        }
        cout << "\nInvalid input\n";
        clientOptions(i);
    }
}

/*
 signIn method that allows a user to sign in
 */
void signIn(){
    
    // Enter the user id and make sure that client exists
    cout << "\nEnter your user ID: ";
    cin >> userId;
    int i = clientExists(userId);
    
    // If client exists then ask for pin
    if (i >= 0){
        if (trace){
            traceFile << getTime() << " --- Unkown user entered " << userId << " as the user ID to sign into\n";
        }
        while (true){
            
            // Enter pin
            cout << "\nEnter your pin or x to cancel: ";
            cin >> pin;
            
            // If the pin matches the pin on the list
            if (pin == clientList[i].getPwd()){
                
                // If the client is the manager then log in is successful
                if (clientList[i].getId() == "manager"){
                    if (trace){
                        traceFile << "\n" << getTime() << " --- The bank manager entered the correct pin and is now logged in.\n";
                    }
                    cout << "\nYou are now logged in as the bank manager.\n\n";
                    manager();
                    break;
                }
                
                // If the client is maintenance then log in is successful
                else if (clientList[i].getId() == "maintenance"){
                    if (trace){
                        traceFile << "\n" << getTime() << " --- The maintenance man entered the correct pin and is now logged in.\n ";
                    }
                    cout << "\nYou are now logged in as the maintenance man.\n\n";
                    maint();
                    break;
                }
                
                // If the client entered the correct pin then log in is successful
                else {
                    if (trace){
                        traceFile << "\n" << getTime() << " --- " << userId << " enetered the correct pin and is now logged in.\n";
                    }
                    cout << "\nYou are now logged in as " << userId << ".\n\n";
                    clientOptions(i);
                    break;
                }
            }
            
            // If pin is x then cancel the process
            else if (pin == "x"){
                if (trace){
                    traceFile << getTime() << " --- Unkown user opted to cancel the sign in process.\n";
                }
                cout << endl;
                menu();
            }
            
            // If the wrong pin was entered return error
            else {
                if (trace){
                    traceFile << getTime() << " --- Unkown user entered the wrong pin to log into " << userId << "'s account.\n";
                }
                cout << "\nInvalid pin.\n";
            }
        }
    }
    
    // If the user ID does not exist then return error
    else {
        if (trace){
            traceFile << getTime() << " --- Unkown user entered " << userId << " as the user ID to sign into, but that user does not exist\n";
        }
        cout << "\nThe user ID entered does not exist.\n\n";
        menu();
    }
}

/*
 signUp method that allows anyone using the app to sign up for an account
 If the manager is opening an account for someone then k will be 5
 */
void signUp(int k){
    
    // Enter the user ID to be associated with the account
    cout << "\nEnter the user ID for your new account: ";
    cin >> userId;
    
    // Check to see if the user already exists
    int i = clientExists(userId);
    
    // If user doesn't exist, then continue
    if (i < 0){
        do {
            if (trace){
                if (k == 5){
                    traceFile << getTime() << " --- Manager entered " << userId << " as the user ID.\n";
                }
                else{
                    traceFile << getTime() << " --- Unknown user entered " << userId << " as their user ID.\n";
                }
            }
            
            // Enter the pin to be associated with the account
            cout << "\nEnter the 4 character pin for your new account: ";
            cin >> pin;
            
            // If pin is of length 4, then continue
            if (pin.length() == 4){
                if (trace){
                    if (k == 5){
                        traceFile << getTime() << " --- Manager entered " << pin << " as the PIN.\n";
                    }
                    else{
                        traceFile << getTime() << " --- Unknown user entered " << pin << " as their PIN.\n";
                    }
                }
                
                // Decide which account to create, push client onto list, and display options
                cout << "\nTo finish creating your new account, you must open either a chequing or savings account\n";
                clientList.push_back(Client(userId, pin));
                i = clientExists(userId);
                
                if (openAccount(i)){
                    cout << "\nAccount with user ID " << userId << " was successfully created.";
                    if(k != 5){
                        cout << "\nYou are now logged in as " << userId << ".\n\n";
                    }
                    
                    if (trace){
                        if(k == 5){
                            traceFile << "\n" << getTime() << " --- " << userId << "'s account was successfully created by the manager.\n";
                        }
                        else{
                            traceFile << "\n" << getTime() << " --- " << userId << "'s account was successfully created and they are now logged in.\n";
                        }
                    }
                    
                    if(k == 5){
                        manager();
                    }
                    else{
                        clientOptions(i);
                    }
                }
                
                // If user decides to cancel process, remove them from client list and go back to main menu
                else {
                    cout << "Account with user ID " << userId << " was not created.\n\n";
                    if (trace){
                        if(k == 5){
                            traceFile << getTime() << " --- Manager failed to create the account " << userId << " because they didn't open a chequing or savings account.\n";
                        }
                        else{
                            traceFile << getTime() << " --- Unkown user failed to create the account " << userId << " because they didn't open a chequing or savings account.\n";
                        }
                    }
                    clientList.pop_back();
                    if(k == 5){
                        manager();
                    }
                    menu();
                }
            }
            
            // If pin is not of length 4 then display error
            else {
                if (trace){
                    if(k == 5){
                        traceFile << getTime() << " --- Manager entered " << pin << " as the pin, but it is invalid.\n";
                    }
                    traceFile << getTime() << " --- Unknown user entered " << pin << " as their pin, but it is invalid.\n";
                }
                cout << "\nInvalid pin\n";
            }
        } while (pin.length() != 4);
    }
    
    // If the user id already exists then return error
    else {
        cout << "\nThat user ID already exists\n\n";
        if (trace){
            if (k == 5){
                traceFile << getTime() << " --- Manager tried to sign up " << userId << ", but they already have an account.\n";
            }
            traceFile << getTime() << " --- Unknown user tried to sign up as " << userId << ", but that account already exists.\n";
        }
        if(k == 5){
            manager();
        }
        menu();
    }
}

/*
 getTime method, thatget's the time
 mainly used for the trace file
 */
string getTime(){
    now = time(0);
    currentTime = ctime(&now);
    return currentTime;
}

/*
 load method that loads up the client info and create the client list
 */
void load(){
    string line;
    string copy;
    int count = 0;
    
    // Open up the text file with the info
    myFile.open("client.txt", ios::in);
    
    // While not the end of file, keep copying each line into a string
    while (getline (myFile,line)){
        // If count = 3
        // Then load the client's Savings info
        if (count == 3){
            count = 0;
            if(line != "no"){
                int i = clientExists(copy);
                float bal = atof(line.c_str());
                clientList[i].setSav(Account(bal, "Sav"));
            }
        }
        
        // If count = 2
        // Then load client's Chequing info
        if (count == 2){
            count++;
            if(line != "no"){
                int i = clientExists(copy);
                float bal = atof(line.c_str());
                clientList[i].setChq(Account(bal, "Chq"));
            }
        }
        
        // If count = 1
        // Then create the client and put them on the list
        if (count == 1){
            count++;
            clientList.push_back(Client(copy, line));
        }
        
        // If count = 0
        // Then copy the user id
        if (count == 0){
            count++;
            copy = line;
        }
    }
    
    // Close the text file
    myFile.close();
}

/*
 menu method, that Creates the main menu
 */
void menu(){
    cout << "Welcome, enter:\n\n 0 to sign in\n 1 to sign up\n q to quit\n\n ";
    cin >> option;
    
    // If 0 is selected, then the user wants to sign in
    if (option == "0"){
        if (trace){
            traceFile << getTime() << " --- Unknown user started sign in process.\n";
        }
        signIn();
    }
    
    // If 1 is selected, then the user wants to sign up for an account
    else if (option == "1"){
        if (trace){
            traceFile << getTime() << " --- Unknown user started sign up process.\n";
        }
        signUp(1);
    }
    
    // If q is selected, save data and then shutdown
    else if (option == "q"){
        if (trace){
            traceFile << getTime() << " --- Unknown user shut down program, execution tracer is turned off.\n";
            traceFile.close();
        }
        
        // Open up the text file
        clientFile.open("client.txt", ios::out);

        // Save the client info
        for (int i = 2; i < clientList.size(); i++){
            
            // Save the id, password, chequing balance, and savings balance on separate lines
            // If a user does not have a chequing or savings account, the balance is replaced with no
            clientFile << clientList[i].getId() << "\n";
            clientFile << clientList[i].getPwd() << "\n";
            if (clientList[i].getChq().getIni()){
                clientFile << clientList[i].getChq().getBal() << "\n";
            }
            else{
                clientFile << "no\n";
            }
            if (clientList[i].getSav().getIni()){
                clientFile << clientList[i].getSav().getBal() << "\n";
            }
            else{
                clientFile << "no\n";
            }
        }
        // Close the file
        clientFile.close();

        // Shut down the program
        exit(0);
    }
    
    // Invalid input, try again
    else {
        if (trace){
            traceFile << getTime() << " --- Unknown user entered invalid input in the main menu.\n";
        }
        cout << "\nInvalid input\n\n";
        menu();
    }
}

/*
 main method
 This is where the program runs.
 The program starts by pushing the manager and maintenance onto the list
 It then loads up any clients and puts them on the list
 Finally, the main menu pops up and the user can use the app
 */
int main() {
    clientList.push_back(Client("manager", "1111"));
    clientList.push_back(Client("maintenance", "1111"));
    load();
    menu();
    return 0;
}