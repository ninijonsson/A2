//
// Created by Nicole Jonsson on 2025-04-22.
//

#include "TransactionSimulator.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

// Deklarera konstruktor
TransactionSimulator::TransactionSimulator(int numOfClients, bool mutexMode)
    // initalBalance på account som parameter
    : account(1000.0), numOfClients(numOfClients), mutexMode(mutexMode) {}

void TransactionSimulator::runSimulation(int durationSeconds)
{
    // Börja med att skapa klienterna
    for (int i = 0; i < numOfClients; ++i)
    {
        // id, referens till BankAccount, mutexMode (true/false)
        clients.push_back(new Client(i, account, mutexMode));
    }

    // Efter att ha skapat dem behöver vi starta dem
    for (auto client : clients)
    {
        // För varje pekare till Client-objekt, anropa start();
        client->start();
    }

    this_thread::sleep_for(chrono::seconds(durationSeconds));

    // Stoppa alla klienter
    for (auto client : clients)
    {
        client->stop();
    }

    // Joina alla trådar med varandra
    for (auto client : clients)
    {
        client->join();
    }

    // Förväntat vs faktiskta balansen
    double expected = 1000.0; // initialBalance till account
    for (auto client : clients)
    {
        expected += client->getTotalTransactions();
    }

    // Faktiskta outcome
    int actual = mutexMode ? account.getBalanceMutex() : account.getBalance();
    double difference = expected - actual;

    cout << "SIMULATION RESULTS:" << endl;
    // cout << "Total transactions including all clients: " << endl;
    cout << "Expected balance: " << expected << endl;
    cout << "Actual balance: " << actual << endl;
    cout << "Discrepancy: " << difference << endl;

    if (abs(difference) <= 0.01)
    {
        cout << "SUCCESS: No race condition detected." << endl;
    } else
    {
        cout << "FAILURE: Race condition detected - balances don't match!" << endl;
    }
}

// Ta bort client
TransactionSimulator::~TransactionSimulator()
{
    for (auto client : clients)
    {
        delete client;
    }
}


