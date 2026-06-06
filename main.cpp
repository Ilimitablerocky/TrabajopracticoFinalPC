#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <queue>
#include "consumidor.h"
#include "productor.h"
#include "paquete.h"
#include "semaforo.h"
#include "gestor.h"

//LIMITES DEL SISTEMA
const int cantidad_Maxima_Paquetes = 1550;
const int cantidad_Maxima_Estanteria = 100;
const int cantidad_Maxima_cinta = 5;

//VARIABLE productor/gestor
int cantidad_actual_estanteria = 0;
chrono::system_clock::time_point inicio_programa = chrono::system_clock::now();

//ESTANTERIA...
Paquete estanteria[cantidad_Maxima_Estanteria];
std::mutex mutex_estanteria;
Semaforo sem_estanteria;
Semaforo sem_espacio_estanteria;

//CINTA...
std::queue<Paquete> cinta;
std::mutex mutex_cinta;
Semaforo sem_cinta;
Semaforo sem_espacio_cinta;


using namespace std;
int main() {
    //SEMAFOROS
    //ESTANTERIA
    init(sem_estanteria, 0);
    init(sem_espacio_estanteria, cantidad_Maxima_Estanteria);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    //productor
    int cantidad_productores = 1;
    int paquetes_x_productor = cantidad_Maxima_Paquetes / cantidad_productores;
    int resto1 = cantidad_Maxima_Paquetes % cantidad_productores;

    // gestor
    thread gest(gestor);

	//productor
    thread prod(productor, 1, paquetes_x_productor);

    //consumidor 1550/3 = 516 resto = 2 quien lo trabaja?
    int cantidad_consumidores = 3;
    int paquetes_x_consumidor = cantidad_Maxima_Paquetes / cantidad_consumidores;
    int resto = cantidad_Maxima_Paquetes % cantidad_consumidores;

    thread consumidor_1(consumidor, 1, paquetes_x_consumidor);
    thread consumidor_2(consumidor, 2, paquetes_x_consumidor);
    thread consumidor_3(consumidor, 3, paquetes_x_consumidor + resto);

    consumidor_1.join();
    consumidor_2.join();
    consumidor_3.join();
    prod.join();
    gest.join();

    return 0;
}

