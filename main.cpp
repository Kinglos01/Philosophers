#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

    std::mutex fork1;
    std::mutex fork2;

void philosopher(int id) {
    while (true) {

        std::cout << "Philosopher " << id << " is thinking.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        if (id == 0) {

            fork1.lock();
            std::cout << "Philosopher 0 picked up fork 1.\n";
            fork2.lock();
            std::cout << "Philosopher 0 picked up fork 2.\n";
        } else {

            fork2.lock();
            std::cout << "Philosopher 1 picked up fork 2.\n";
            fork1.lock();
            std::cout << "Philosopher 1 picked up fork 1.\n";
        }


        std::cout << "Philosopher " << id << " is eating.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));


        fork1.unlock();
        fork2.unlock();
        std::cout << "Philosopher " << id << " put down both forks.\n";
    }
}

int main() {
    std::thread phil0(philosopher, 0);
    std::thread phil1(philosopher, 1);

    phil0.join();
    phil1.join();

    return 0;

}
