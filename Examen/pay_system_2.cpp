#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <queue>
#include "estructura.h"

std::queue<std::shared_ptr<peticion>> pet_queue;
std::mutex g_mtx;

int main(int argc, char const *argv[])
{

    return 0;
}

cliente()
{
    std::shared_ptr<peticion> pet = std::make_shared<peticion>();
    pet->balance = 100;
    pet->pago = 10;
    pet->mtx.lock();
    pet->id = 0;

    std::unique_lock<std::mutex> lck (g_mtx);
    pet_queue.push(pet);
    lck.unlock();

    


}
