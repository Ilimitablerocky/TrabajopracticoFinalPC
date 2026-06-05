#include "gestor.h"

void gestor(int cantidad_Maxima_paquetes, int& cant_estanteria, Paquete estanteria[], 
            queue<Paquete>& cinta, chrono::system_clock::time_point inicio_programa,
            Semaforo& sem_estanteria, Semaforo& sem_espacio_estanteria,
            Semaforo& sem_espacio_cinta, Semaforo& sem_cinta_llena,
            Semaforo& mutex_estanteria, Semaforo& mutex_cinta) {  
    int procesados = 0;

    while (procesados < cantidad_Maxima_paquetes) {

        wait(sem_estanteria);  // Espera a un paquete en la estanteria

        
        wait(mutex_estanteria);  // Se bloquea el mutex de la estanteria
            Paquete p = buscar_mayor_prioridad(estanteria, cant_estanteria); // Busca y obtiene el paquete de mayor prioridad en la estanteria
            cant_estanteria--;  // Se reduce la cantidad de paquetes en la estanteria 
        signal(mutex_estanteria);  // Se desbloquea el mutex de la estanteria

        signal(sem_espacio_estanteria);  // Se da aviso de que hay espacio en la estanteria para el productor
      
        this_thread::sleep_for(chrono::milliseconds(420));  // Se espera 420ms simulando trafico o congestion

        wait(sem_espacio_cinta);  // Se espera a que haya espacio en la cinta

        wait(mutex_cinta); // Se bloquea el mutex de la cinta
            p.ingreso_cinta = chrono::system_clock::now();  // Se guarda el momento de ingreso a la cinta
            cinta.push(p);  // se coloca el paquete en la cinta
            cout << "Gestor coloco paquete ID = " << p.id           //  Print para verificar los id de los paquetes 
                 << " -- Prioridad = " << p.prioridad      //  Print para ver que la prioridad sea la correcta
                 << " -- Ingreso a la cinta = " << chrono::duration_cast<chrono::milliseconds>(p.ingreso_cinta - inicio_programa).count() << "ms" << endl; //  Print para ver el tiempo de ingreso del paquete a la cinta
        signal(mutex_cinta);  // Se desbloquea el mutex de la cinta

        signal(sem_cinta_llena);  // Se avisa de un nuevo paquete en la cinta para el consumidor

        procesados++;
    }
}
