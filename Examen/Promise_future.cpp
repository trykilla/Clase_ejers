#include <iostream>
#include <functional>
#include <thread>
#include <future>

void print(std::future<int> &fut)
{
    std::cout << "Waiting for value..." << std::endl;
    int x = fut.get();
    std::cout << "This is what I got: " << x << std::endl;  

}

int main(int argc, char const *argv[])
{
    std::promise<int> prom;

    std::future<int> fut = prom.get_future();

    std::thread t1 (print, std::ref(fut));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    prom.set_value(10);

    t1.join();
    return 0;
}
