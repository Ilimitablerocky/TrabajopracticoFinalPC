#include "productor.h"


int generar_prioridad_con_frecuencia(int intervalo_cero) {
    static int contador = 0;
    contador++;
        if (contador == intervalo_cero) {
        contador = 0; // Reiniciar el ciclo
        return 0;
    }
    return 1;
}

void productor(int id, int paquetes_x_productor){

    for(int i=0; i < paquetes_x_productor; i++){

        Paquete nuevo;
        int x = generar_prioridad_con_frecuencia(40);
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
