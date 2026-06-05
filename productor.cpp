#include "productor.h"

int generar_prioridad_aleatoria(){

    auto ahora = std::chrono::system_clock::now().time_since_epoch().count();
    return (ahora/100000) %2;

};

void productor(int id, int paquetes_x_productor){

    for(int i=0; i < paquetes_x_productor; i++){

        Paquete nuevo;
        int x = generar_prioridad_aleatoria();
        Crear_Paquete(nuevo,i,x);

        wait(sem_espacio_estanteria);

        mutex_estanteria.lock();
            estanteria[cantidad_actual_estanteria] = nuevo;
            cantidad_actual_estanteria++;
        mutex_estanteria.unlock();

        signal(sem_estanteria);

        std::this_thread::sleep_for(std::chrono::milliseconds(90));
        std::cout<< "Productor: " << id << " Almaceno paquete en la estanteria prioridad: " << nuevo.prioridad <<std::endl;
    }




};
