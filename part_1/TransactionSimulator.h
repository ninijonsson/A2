//
// Created by Nicole Jonsson on 2025-04-22.
//

#ifndef TRANSACTION_SIMULATOR_H
#define TRANSACTION_SIMULATOR_H

#include <vector> // För att hålla koll på alla Clients och trådar
#include "Client.h"
#include "BankAccount.h"

using namespace std;

class TransactionSimulator {
    private:
        BankAccount account;
        // Om objekt innehåller en thread, måste pekare användas för att undvika kopiering
        vector<Client*> clients; // Pekare till klienterna, vi vill inte ha kopior av klienterna
        int numOfClients;
        bool mutexMode; // om true är det med mutex

    public:
        // Konstruktor
        TransactionSimulator(int numOfClients, bool mutexMode = false);

        // Destruktor
        ~TransactionSimulator(); // Utan att ta bort Client* försvinner dem aldrig tas bort -> memory leaks

        void runSimulation(int durationSeconds);
};

#endif //TRANSACTION_SIMULATOR_H
