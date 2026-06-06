#ifndef CONSUMIDOR_H_INCLUDED
#define CONSUMIDOR_H_INCLUDED

#include <queue>
#include <thread>
#include "semaforo.h"
#include "paquete.h"

extern const int cantidad_Maxima_cinta;
extern std::queue<Paquete> cinta;
extern std::mutex mutex_cinta;
extern Semaforo sem_cinta;
extern Semaforo sem_espacio_cinta;

extern std::mutex mutex_consola;

void consumidor(int id_consumidor, int paquetes_x_consumidores);

#endif // CONSUMIDOR_H_INCLUDED
