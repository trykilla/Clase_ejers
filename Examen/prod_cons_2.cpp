#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <vector>

#define MAX_BUFF 5

std::condition_variable prod_cv;
std::condition_variable cons_cv;
std::mutex g_prod_mtx;
std::mutex g_cons_mtx;
std::vector<int> sh_buffer;

void productor()
{

    while (1)
    {
        std::unique_lock<std::mutex> lck(g_prod_mtx);
        prod_cv.wait(lck, []()
                     { return sh_buffer.size() < MAX_BUFF; });

        sh_buffer.push_back(1);
        std::cout << "Producing..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cons_cv.notify_one();
    }
}

void consumidor()
{
    while (1)
    {
        std::unique_lock<std::mutex> lck(g_cons_mtx);
        cons_cv.wait(lck, []()
                     { return !sh_buffer.empty(); });

        sh_buffer.pop_back();
        std::cout << "Consuming..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        prod_cv.notify_one();
    }
}

int main(int argc, char *argv[])
{

    std::thread prod_th(productor);
    std::thread cons_th(consumidor);

    prod_th.join();
    cons_th.join();

    return EXIT_SUCCESS;
}
