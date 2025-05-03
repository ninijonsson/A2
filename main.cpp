#include <iostream>
#include "main.h"
#include "part_1/TransactionSimulator.h"
#include "part_2/Account.h"
#include "part_2/AccountNoDeadlock.h"
#include <thread>

using namespace std;

// PART 1
int main() {
    // PART 1
    // Fall 1: Utan mutex
    noMutex();

    // Fall 2: Med mutex
    withMutex();

    cout << "" << endl;

    // PART 2
    // Fall 1: Deadlock
    //deadlock();

    // Fall 2: Undvika deadlock
    noDeadlock();

    return 0;
}

void noMutex()
{
    cout << "\n--- UNSYNCHRONIZED SIMULATION ---" << endl;
    TransactionSimulator unsynchronizedSimulation(10, false);
    unsynchronizedSimulation.runSimulation(3);
}

void withMutex()
{
    cout << "\n--- SYNCHRONIZED SIMULATION ---" << endl;
    TransactionSimulator synchronizedSimulation(10, true);
    synchronizedSimulation.runSimulation(3);
}

void deadlock()
{
    Account account1(1, 1000);
    Account account2(2, 1000);

    // Lambda-uttryck i C++
    // [&] = fånga alla omgivande variabler som används i lambdan med referens
    // [=] = fånga allt som används som kopia
    thread thread1([&]()
    {
        account1.transfer(account2, 100);
    });

    thread thread2([&]()
    {
        account2.transfer(account1, 200);
    });

    thread1.join();
    thread2.join();

    cout << "--- FINAL BALANCES ---" << endl;
    cout << "Account 1: " << account1.balance << endl;
    cout << "Account 2: " << account2.balance << endl;
}

void noDeadlock()
{
    AccountNoDeadlock account1(1, 1000);
    AccountNoDeadlock account2(2, 1000);

    thread thread1([&]()
    {
        account1.transfer(account2, 400);
    });

    thread thread2([&]()
    {
        account2.transfer(account1, 100);
    });

    thread1.join();
    thread2.join();

    cout << "\n--- FINAL BALANCES ---" << endl;
    cout << "Account 1: " << account1.balance << endl;
    cout << "Account 2: " << account2.balance << endl;
}