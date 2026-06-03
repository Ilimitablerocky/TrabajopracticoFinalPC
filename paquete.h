#ifndef PAQUETE_H_INCLUDED
#define PAQUETE_H_INCLUDED
#include <iostream>
#include <chrono>

struct Paquete{
    int id;
    int prioridad;
    std::chrono::system_clock::time_point creacion;
    std::chrono::system_clock::time_point ingreso_cinta;
};

void Crear_Paquete(Paquete& p, int nro, int prioridad);
void mostrar_Paquete(Paquete& p);
#endif // PAQUETE_H_INCLUDED
