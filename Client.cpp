//
// Created by Nicole Jonsson on 2025-04-22.
//

#include "Client.h"
#include <random> // För alla random deposits och withdrawals
#include <chrono> // Används för tid såsom sekunder
#include <thread> // För att kunna göra det multitrådat
#include <iostream>

using namespace std;

Client::Client(int id, BankAccount& account, bool mutexMode)
    : clientID(id), account(account), mutexMode(mutexMode), stopSignal(false), totalTransactions(0) {}

// Startar tråd
// Referens till Clients run-metod som körs
// Tråden behöver veta vilket Client-objekt, därav this
void Client::start()
{
    clientThread = thread(&Client::run, this);
}

// Stannar tråden med flagga
void Client::stop()
{
    stopSignal = true;
}

// Vänta på att clientThread ska bli klar innan vi går vidare
void Client::join()
{
    clientThread.join();
}

double Client::getTotalTransactions()
{
    lock_guard<mutex> lock(mtx);
    return totalTransactions;
}

// Metoden som körs när tråden skapas
void Client::run()
{
    random_device random; // Random siffra
    mt19937 randomGenerator(random());
    uniform_real_distribution<double> randomAmount(10.0, 100.0);
    uniform_int_distribution<int> depositOrWithdrawal(0, 1);

    while (!stopSignal)
    {
        // För varje iteration
        double amount = randomAmount(randomGenerator);
        bool toDeposit = depositOrWithdrawal(randomGenerator);

        lock_guard<mutex> lock(mtx);
        if (mutexMode)
        {
            if (toDeposit)
            {
                account.depositMutex(amount);
                totalTransactions += amount;
            } else
            {
                account.withdrawMutex(amount);
                totalTransactions -= amount;
            }
        } else
        {
            if (toDeposit)
            {
                account.deposit(amount);
                totalTransactions += amount;
            } else
            {
                account.withdraw(amount);
                totalTransactions -= amount;
            }
        }

        // Skapa race condition
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
