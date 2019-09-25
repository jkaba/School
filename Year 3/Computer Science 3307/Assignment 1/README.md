# C++ Assignment

## Introduction:
- This assignment is to build an Object-oriented program through the implementation of a banking system in C++.
- The banking system enables customers of a financial institution to perform financial transactions  without the need for a human cashier. In this respect, it is a like an automated teller system (ATM). However, the banking system is more than an ATM as there are other agents involved, such as the bank manager and a system maintainer, as described below.

## System Description:
- The bank has an unspecified number of customers. For demonstration purposes, you can have a manageable number of test customers. The term “client” is a synonym for the term “customer”. Each customer has either or both of a savings account and a chequing account.
- There is a bank manager who has managerial powers to open and close an account and see the critical details of a particular, or all (at once), customers in a formatted display.
- When a client wants to open a new account at the bank, it is assumed that s/he will contact the manager (e.g., in a face-to-face meeting) and ask him/her to create the desired account. Therefore, clients do not have the power to open a new account.
- Once a customer has been given an account by the manager, s/he has access to use only his/her account. In a given user session with the bank, the customer will be provided the capabilities to use multiple operations in that session (e.g., withdraw funds from the chequing account, transfer funds to the deposit account, print recent transactions, etc.).
- Each user of the system, regardless of his/her role type, has an “id” for secure login. After logging into the system, s/he will be bounded by his/her role as to what s/he can do with this system.
- There is also a role of a systems maintenance person who also has an “id” to access the system. S/he can turn ON/OFF the system’s execution trace.
- An execution trace is a log of the system’s functions entered, along with the time entered, during the use of the system by the user. In order to associate a particular trace with the user that generated it, the user is identified at the head of the execution trace.
- When the trace switch is set to ON, an execution trace is written, for a given account, in an external file that can be printed out at a later time by the maintenance person. No traces are generated when the switch is in the OFF state.

## Features:
- Open/Close an account; close restricted to zero balance accounts.
- Deposit to, and withdraw money from, an account.
- Give warning messages for not sufficient funds (e.g., when withdrawing).
- Transfer a sum from one account to another.
- Obtain account balances.
- Give a warning message to the client if the balance on his/her “chequing” account will drop below the threshold of $1,000 – prior to him/her executing the operation. If s/he decides to go ahead despite the warning message, a charge of $2.00 is levied on the client for each such transaction. This levy is applied only once, when there is a crossover from above to below the threshold.
- Upon a client’s assumed face-to-face meeting with the manager to open an account, the manager will open either a savings or a chequing account, or both. Later, the client can request the manager to add the complementary account at anytime.
- The bank manager can display the account details of any given customer, or all customers, and obtain aggregate data on the funds in the bank, etc., categorised appropriately.
- Funds in the account transcend the duration of a particular user session with the bank.
- A client can transfer funds to another user’s chequing/savings account
- Any user can sign up for an account through the app
- A client can display their transaction history
- The Manager can view a list of all clientele
