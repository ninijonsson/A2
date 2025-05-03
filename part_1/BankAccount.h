//
// Created by Nicole Jonsson on 2025-04-22.
//

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <mutex> // För att kunna synkronisera

using namespace std;

class BankAccount {
    private:
        int id;
        double balance;
        mutex mtx;

    public:
        // Konstruktor
        BankAccount(double initialBalance);

        // Metoder, utan att använda mutex
        void deposit(double amount);
        void withdraw(double amount);
        double getBalance();

        // Metoder med mutex
        void depositMutex(double amount);
        void withdrawMutex(double amount);
        double getBalanceMutex();
};

#endif //BANKACCOUNT_H
