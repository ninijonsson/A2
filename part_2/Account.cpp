//
// Created by Nicole Jonsson on 2025-05-03.
//

#include "Account.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Initialisering av konstruktorn
Account::Account(int id, int balance) : id(id), balance(balance) {}

void Account::transfer(Account& toAccount, int amount)
{
    cout << "Thread " << this_thread::get_id() << ": Trying to lock 'Account " << id << "'" << endl;
    lock_guard<mutex> lock1(mtx); // Lås tråd 1
    this_thread::sleep_for(chrono::milliseconds(500)); // Så att allting inte sker samtidigt

    cout << "Thread " << this_thread::get_id() << ": Locked 'Account " << id
    << "' trying to lock 'Account " << toAccount.id << "'" << endl;
    lock_guard<mutex> lock2(mtx); // Lås tråd 2

    // Kontrollera så att vi har tillräckligt med pengar på kontot
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
