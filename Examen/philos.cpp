#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>
#include <vector>
#include <memory>
#include <algorithm>
#include <ctime>

#define NUM_PHILOS 5;

void philo(int id);

std::vector<int> forks;
std::vector<std::thread> v_threads;
std::mutex g_mtx;
std::condition_variable pito;

int main(int argc, char const *argv[])
{
    forks.push_back(1);
    forks.push_back(1);

    for (int i = 0; i < 5; i++)
    {
        v_threads.push_back(std::thread(philo, i));
    }

    std::for_each(v_threads.begin(), v_threads.end(), [](std::thread &t)
                  { t.join(); });

    return 0;
}

void philo(int id)
{

    while (1)
    {
        std::cout << "Philoshoper " << id << " thinking..." << std::endl;

        std::unique_lock<std::mutex> lck(g_mtx);
        pito.wait(lck, []()
                  { return forks.size() >= 1; });

        forks.pop_back();
        lck.unlock();

        std::cout << "Philoshoper " << id << " eating..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Philoshoper " << id << " has eaten..." << std::endl;

        lck.lock();
        forks.push_back(1);
        lck.unlock();

        pito.notify_one();
    }
}