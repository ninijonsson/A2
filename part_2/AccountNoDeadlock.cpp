//
// Created by Nicole Jonsson on 2025-05-03.
//

#include "AccountNoDeadlock.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm> // För att använda swap()-metoden

using namespace std;

// Initialisering av konstruktor
AccountNoDeadlock::AccountNoDeadlock(int id, int balance) :
    id(id), balance(balance) {}

void AccountNoDeadlock::transfer(AccountNoDeadlock& toAccount, int amount)
{
    // Pekare, inte kopior på objekten!
    AccountNoDeadlock* first = this;
    AccountNoDeadlock* second = &toAccount;

    // Kontrollera så att låsningen sker i ordning
    // för att undvika deadlock
    // Så om toAccounts id är mindre än detta objektets id ska vi byta plats på dem
    // eftersom vi har satt att this ska vara "first" och &toAccount ska vara "second"
    if (toAccount.id < this->id)
    {
        // Byter innehållet mellan två variabler
        swap(first, second);
    }

    // Med denna checken testar vi låsa igen
    cout << "Thread " << this_thread::get_id() <<
        ": Trying to lock 'Account " << id << "'" << endl;
    lock_guard<mutex> lock1(first->mtx); // Låser tråden
    this_thread::sleep_for(chrono::milliseconds(500));

    cout << "Thread " << this_thread::get_id() << ": Locked 'Account " << id <<
        "' trying to lock 'Account " << toAccount.id << endl;
    lock_guard<mutex> lock2(second->mtx);

    // Kontrollera så att pengarna finns på kontot
    if (balance >= amount)
    {
        balance -= amount;
        toAccount.balance += amount;
        cout << "Thread " << this_thread::get_id() << ": Transferred " << amount <<
            " from 'Account " << id << "'" << endl;
    } else
    {
        cout << "Thread " << this_thread::get_id() << ": Insufficient funds in 'Account " <<
            id << "'" << endl;
    }
}

