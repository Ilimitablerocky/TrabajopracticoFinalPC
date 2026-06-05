#include <queue>
#include <thread>
#include <chrono>
#include <iostream>
#include "paquete.h"
#include "semaforo.h"

using namespace std;

void gestor(int cantidad_Maxima_paquetes, int& cant_estanteria, Paquete estanteria[], 
            queue<Paquete>& cinta, chrono::system_clock::time_point inicio_programa,
            Semaforo& sem_estanteria, Semaforo& sem_espacio_estanteria,
            Semaforo& sem_espacio_cinta, Semaforo& sem_cinta_llena,
            Semaforo& mutex_estanteria, Semaforo& mutex_cinta);
