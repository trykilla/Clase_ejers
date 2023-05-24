#include <iostream>
#include <functional>
#include <thread>
#include <future>
#include <exception>

void print(std::future<int> &fut)
{
    try
    {
        std::cout << "Waiting for value: " << std::endl;
        int x = fut.get();
        std::cout << "Value: " << x << std::endl;
    }
    catch (std::exception &)
    {
        std::cout << "Exception!" << std::endl;
        
    }
}

int main(int argc, char const *argv[])
{
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread t(print, std::ref(fut));

    int x = 0;
    std::cout << "Introduce un valor entero: " << std::endl;
    std::cin.exceptions(std::ios::failbit);

    try
    {
        std::cin >> x;
        prom.set_value(x);
    }
    catch (std::exception &)
    {
        prom.set_exception(std::current_exception());
    }

    t.join();
    return 0;
}
