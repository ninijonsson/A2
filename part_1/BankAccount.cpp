//
// Created by Nicole Jonsson on 2025-04-22.
//

#include "BankAccount.h"

#include <iostream>
#include <string>
#include <mutex>

using namespace std;

BankAccount::BankAccount(double initialBalance) : balance(initialBalance) {} // Istället för balance = initialBalance;

// Utan mutex
void BankAccount::deposit(double amount)
{
    balance += amount;
}

void BankAccount::withdraw(double amount)
{
    balance -= amount;
}

double BankAccount::getBalance()
{
    return balance;
}

// Med mutex
void BankAccount::depositMutex(double amount)
{
    lock_guard<mutex> lock(mtx); // Låser
    balance += amount;
}

void BankAccount::withdrawMutex(double amount)
{
    lock_guard<mutex> lock(mtx); // Låser
    balance -= amount;
}

double BankAccount::getBalanceMutex()
{
    lock_guard<mutex> lock(mtx); // Låser
    return balance;
}
