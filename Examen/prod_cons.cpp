#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

#define MAX_BUFF 5

std::mutex cons_mtx;
std::mutex prod_mtx;
std::condition_variable cv_prod;
std::condition_variable cv_cons;
std::queue<int> sh_queue;

void producer(int id);
void consumer(int id);

int main()
{
    std::thread t1(producer, 0);
    std::thread t2(consumer, 1);

    t1.join();
    t2.join();

    return EXIT_SUCCESS;
}

void producer(int id)
{
    while (1)
    {
        srand(time(NULL));
        std::unique_lock<std::mutex> lck(prod_mtx);
        cv_prod.wait(lck, []()
                     { return sh_queue.size() < MAX_BUFF; });
        int n = rand() % 100;
        std::cout << "Producing element..." << std::endl;
        sh_queue.push(n);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cv_cons.notify_one();
    }
}

void consumer(int id)
{
    while (1)
    {
        std::unique_lock<std::mutex> lck(cons_mtx);
        cv_cons.wait(lck, []()
                     { return !sh_queue.empty(); });
        std::cout << "Consuming element..." << std::endl;
        sh_queue.pop();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        cv_prod.notify_one();
    }
}
