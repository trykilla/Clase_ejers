/*
Crear
sistema de pago sencillo
(singleton) que atienda peticiones
de una cola. Cada petición debe
incluir id del hilo solicitante,
cantidad a pagar, saldo y
semáforo que bloquee al
pagador. El sistema de pago
debe restar la cantidad del saldo
y enviar notificación
*/

#include "struct.h"
#include <vector>
#include <iostream>
#include <atomic>
#include <algorithm>
#include <condition_variable>
#include <queue>

#define N 4

void client(int id);
void pay_system();

std::vector<std::thread> v_threads;
std::condition_variable pay_cv;
std::queue<std::shared_ptr<peticion>> clients_queue;
std::mutex g_mtx;

int main(int argc, char const *argv[])
{
    for (int i = 0; i < N; i++)
    {
        v_threads.push_back(std::thread(client, i));
    }
    std::thread t(pay_system);
    t.detach();

    std::for_each(v_threads.begin(), v_threads.end(), [](std::thread &t)
                  { t.join(); });

    return 0;
}

void client(int id)
{

    std::shared_ptr<peticion> pet = std::make_shared<peticion>();
    pet->mtx.lock();
    pet->th_id = id;
    pet->quantity = 100;
    pet->payment = 50;

    std::unique_lock<std::mutex> lck(g_mtx);
    clients_queue.push(pet);
    lck.unlock();

    std::cout << "Se va a realizar el pago..." << std::endl;
    pay_cv.notify_one();
    pet->mtx.lock();
    std::cout << "Pago realizado..." << std::endl;
}

void pay_system()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    while (1)
    {
        std::unique_lock<std::mutex> lck(g_mtx);
        pay_cv.wait(lck, []()
                    { return !clients_queue.empty(); });
        std::cout << "Realizando pago para el cliente " << clients_queue.front()->th_id << std::endl;
        clients_queue.front()->quantity = clients_queue.front()->quantity - clients_queue.front()->payment;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        clients_queue.front()->mtx.unlock();
        clients_queue.pop();

    }
}