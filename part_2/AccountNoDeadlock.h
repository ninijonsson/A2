//
// Created by Nicole Jonsson on 2025-05-03.
//

#ifndef ACCOUNTNODEADLOCK_H
#define ACCOUNTNODEADLOCK_H

#include <mutex>

using namespace std;

class AccountNoDeadlock
{
public:
    int id;
    int balance;
    mutex mtx;

    // Konstruktor
    AccountNoDeadlock(int id, int balance);

    // Metoder
    void transfer(AccountNoDeadlock& toAccount, int amount);
};

#endif //ACCOUNTNODEADLOCK_H
