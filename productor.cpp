#include "productor.h"


int generar_prioridad_con_frecuencia(int cada_cuantos_paquetes) {
    static int contador = 0;
    contador++;
        if (contador == cada_cuantos_paquetes) {
        contador = 0; // Reinicia el ciclo
        return 0;
    }
    return 1;
}

void productor(int id, int paquetes_x_productor){

    for(int i=0; i < paquetes_x_productor; i++){

        Paquete nuevo;
        int x = generar_prioridad_con_frecuencia(frecuencia_prioridad_0);

        mutex_idpaquete.lock(); //protegemos el contador de paquetes
        int id_temp = numero_paquete; // asignamos id_temp a una variable global la cual va incrementando
        numero_paquete++; // se incrementa
        mutex_idpaquete.unlock();
        
        Crear_Paquete(nuevo,id_temp+1,x);                                  //(producir paquete)

        wait(sem_espacio_estanteria);

        std::this_thread::sleep_for(std::chrono::milliseconds(90)); //(colocar en estanteria)

        mutex_estanteria.lock();
        estanteria[cantidad_actual_estanteria] = nuevo;
        cantidad_actual_estanteria++;
        if(nuevo.prioridad == 0){
            cant_producidos_p0++;
        }else{
            cant_producidos_p1++;
        }
        mutex_estanteria.unlock();

        signal(sem_estanteria);

        mutex_consola.lock();
        std::cout<< "Productor con ID: " << id << ", almaceno paquete ID: " << nuevo.id << " con prioridad: " << nuevo.prioridad << " en la estanteria." << std::endl;
        mutex_consola.unlock();
    }

};
