//
// Created by Nicole Jonsson on 2025-05-03.
//

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <mutex>

using namespace std;

class Account
{
    public:
        int id;
        int balance;
        mutex mtx;

        // Konstruktor
        Account(int id, int balance);

        // Metoder
        void transfer(Account& toAccount, int amount);
};

#endif //ACCOUNT_H
