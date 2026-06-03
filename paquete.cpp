#include "paquete.h"

void Crear_Paquete(Paquete& p, int nro, int prioridad){
    p.id = nro;
    p.prioridad = prioridad;
}

void mostrar_Paquete(Paquete& p){
    std::cout << "Paquete: " << p.id << std::endl;
    std::cout << "Prioridad: " << p.prioridad << std::endl;
    std::cout << "Fecha Creacion: " << "FECHA_DE_CREACION" << std::endl;
}
