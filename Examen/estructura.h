#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>
#include <functional>
#include <mutex>

struct peticion
{
    int id;
    int balance;
    int pago;
    std::mutex mtx;
};