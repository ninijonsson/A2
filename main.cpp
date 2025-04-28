#include <iostream>

using namespace std;

#include "TransactionSimulator.h"

int main() {
    // Fall 1: Utan mutex
    cout << "UNSYNCHRONIZED SIMULATION" << endl;
    TransactionSimulator unsynchronizedSimulation(10, false);
    unsynchronizedSimulation.runSimulation(3);

    cout << " " << endl;

    // Fall 2: Med mutex
    cout << "SYNCHRONIZED SIMULATION" << endl;
    TransactionSimulator synchronizedSimulation(10, true);
    unsynchronizedSimulation.runSimulation(3);

    return 0;
}
