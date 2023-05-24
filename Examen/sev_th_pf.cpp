#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>
#include <functional>
#include <chrono>
#include <future>

void print(const int id, std::shared_future<int> &fut)
{
    int x = fut.get();
    std::cout << "Th id: " << id << std::endl;
    if (x == id)
        std::cout << "Th id: " << id << " is my turn. " << std::endl;
    else 
        std::cout << "Th id: " << id << " is my turn. " << std::endl;
}

int main(int argc, char const *argv[])
{
    int turn = -1;

    std::promise<int> prom;
    std::shared_future<int> fut(prom.get_future());

    std::thread t1(print, 1, std::ref(fut));
    std::thread t2(print, 2, std::ref(fut));

    std::this_thread::sleep_for(std::chrono::seconds(2));

    turn = (rand() % 2) + 1;
    std::cout << turn << std::endl;

    prom.set_value(turn);
    t1.join();
    t2.join();

    return 0;
}
