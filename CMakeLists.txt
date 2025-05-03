cmake_minimum_required(VERSION 3.30)
project(A2)

set(CMAKE_CXX_STANDARD 20)

add_executable(A2 main.cpp
        part_1/BankAccount.cpp
        part_1/BankAccount.h
        part_1/Client.cpp
        part_1/Client.h
        part_2/DeadlockSimulator.cpp
        part_2/DeadlockSimulator.h
        part_1/TransactionSimulator.cpp
        part_1/TransactionSimulator.h
        part_2/AccountNoDeadlock.cpp
        part_2/AccountNoDeadlock.h
        part_2/Account.cpp
        part_2/Account.h
)
