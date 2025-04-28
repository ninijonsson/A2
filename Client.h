//
// Created by Nicole Jonsson on 2025-04-22.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <thread>
#include <mutex>
#include <atomic> // Operationer sker helt eller inte alls -> thread-safe
#include "BankAccount.h"

using namespace std;

class Client {
    private:
        int clientID;
        int totalTransactions; // Summering av antal transaktioner av denna klienten
        bool mutexMode; // Om denna är true används metoderna med mutex
        BankAccount& account; // Referens till bankkonto, ska vara en och samma
        thread clientThread;
        atomic<bool> stopSignal;

        void run(); // Trådmetod

    public:
        // Konstruktor
        Client(int id, BankAccount& account, bool mutexMode = false);

        // Metoder
        void start();
        void stop();
        void join();
        double getTotalTransactions() const;
};

#endif //CLIENT_H
