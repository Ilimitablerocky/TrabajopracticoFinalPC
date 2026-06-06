#include "gestor.h"

void gestor() {  
    int procesados = 0;

    while (procesados < cantidad_Maxima_Paquetes) {

        wait(sem_estanteria);  // Espera a un paquete en la estanteria

        
        mutex_estanteria.lock(); // Se bloquea el mutex de la estanteria
            Paquete p = buscar_mayor_prioridad(estanteria, cantidad_actual_estanteria); // Busca y obtiene el paquete de mayor prioridad en la estanteria
            cantidad_actual_estanteria--;  // Se reduce la cantidad de paquetes en la estanteria 
        mutex_estanteria.unlock();  // Se desbloquea el mutex de la estanteria

        signal(sem_espacio_estanteria);  // Se da aviso de que hay espacio en la estanteria para el productor
      
        this_thread::sleep_for(chrono::milliseconds(420));  // Se espera 420ms simulando trafico o congestion

        wait(sem_espacio_cinta);  // Se espera a que haya espacio en la cinta

        mutex_cinta.lock(); // Se bloquea el mutex de la cinta
            p.ingreso_cinta = chrono::system_clock::now();  // Se guarda el momento de ingreso a la cinta
            cinta.push(p);  // se coloca el paquete en la cinta
            cout << "Gestor coloco paquete ID = " << p.id           //  Print para verificar los id de los paquetes 
                 << " -- Prioridad = " << p.prioridad      //  Print para ver que la prioridad sea la correcta
                 << " -- Ingreso a la cinta = " << chrono::duration_cast<chrono::milliseconds>(p.ingreso_cinta - inicio_programa).count() << "ms" << endl; //  Print para ver el tiempo de ingreso del paquete a la cinta
        mutex_cinta.unlock();  // Se desbloquea el mutex de la cinta

        signal(sem_cinta);  // Se avisa de un nuevo paquete en la cinta para el consumidor

        procesados++;
    }
}
