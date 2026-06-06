#include <queue>
#include <thread>
#include <chrono>
#include <iostream>
#include "paquete.h"
#include "semaforo.h"

using namespace std;
extern const int cantidad_Maxima_Paquetes;
extern const int cantidad_Maxima_Estanteria;
extern const int cantidad_Maxima_cinta;

//VARIABLE productor/gestor
extern int cantidad_actual_estanteria;
extern chrono::system_clock::time_point inicio_programa;

//ESTANTERIA...
extern Paquete estanteria[];
extern std::mutex mutex_estanteria;
extern Semaforo sem_estanteria;
extern Semaforo sem_espacio_estanteria;

//CINTA...
extern std::queue<Paquete> cinta;
extern std::mutex mutex_cinta;
extern Semaforo sem_cinta;
extern Semaforo sem_espacio_cinta;

extern std::mutex mutex_consola;

void gestor();
