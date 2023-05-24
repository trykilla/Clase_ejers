#include <iostream>
#include <thread>
#include <mutex>

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

struct peticion
{

    int th_id;
    double payment;
    double quantity;
    std::mutex mtx;

};
