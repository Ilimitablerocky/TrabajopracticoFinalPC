#ifndef PRODUCTOR_H_INCLUDED
#define PRODUCTOR_H_INCLUDED
#include "paquete.h"
#include "semaforo.h"
#include <thread>

extern const int cantidad_Maxima_cinta;

//VARIABLE productor/gestor
extern int cantidad_actual_estanteria;
extern int numero_paquete;
extern int cant_producidos_p1;
extern int cant_producidos_p0;

//ESTANTERIA...
extern Paquete estanteria[];
extern std::mutex mutex_estanteria;
extern Semaforo sem_estanteria;

extern std::mutex mutex_consola;
extern std::mutex mutex_idpaquete;

int generar_prioridad_con_frecuencia(int cada_cuantos_paquetes);

void productor(int id, int paquetes_x_productor, int cada_cuantos_paquetes);

#endif // PRODUCTOR_H_INCLUDED
