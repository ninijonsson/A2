#include <iostream>

using namespace std;

#include <iostream>
#include <thread>

int counter = 0;
mutex mtx;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        // lock_guard<mutex> lock(mtx);
        // Utan mutex kommer det bli fel värde på counter
        ++counter;
    }
}

int main() {
    thread t1(increment); // Skapa tråd
    thread t2(increment);
    t1.join();
    t2.join();

    cout << "Counter: " << counter << endl;
    return 0;
}
