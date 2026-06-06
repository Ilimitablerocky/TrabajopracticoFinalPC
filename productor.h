#ifndef PRODUCTOR_H_INCLUDED
#define PRODUCTOR_H_INCLUDED
#include "paquete.h"
#include "semaforo.h"
#include <thread>

extern const int cantidad_Maxima_Paquetes;
extern const int cantidad_Maxima_Estanteria;
extern const int cantidad_Maxima_cinta;

//VARIABLE productor/gestor
extern int cantidad_actual_estanteria;
extern int numero_paquete;
extern std::mutex mutex_idpaquete;

//ESTANTERIA...
extern Paquete estanteria[];
extern std::mutex mutex_estanteria;
extern Semaforo sem_estanteria;
extern Semaforo sem_espacio_estanteria;

extern std::mutex mutex_consola;

int generar_prioridad_aleatoria();

void productor(int id, int paquetes_x_productor);

#endif // PRODUCTOR_H_INCLUDED
