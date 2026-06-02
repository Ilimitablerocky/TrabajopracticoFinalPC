#include "gestor.h"

//void gestor() {  //Dejo documentado que hay que revisar el nombre de la funcion Buscar_mayor_prioridad() y agregar el nombre correcto del .h en el archivo gestor.h
    int procesados = 0;

    while (procesados < cantidad_Maxima_paquetes) {

        wait(sem_estanteria);  // Espera a un paquete en la estanteria

        
        wait(mutex_estanteria);  // Se bloquea el mutex de la estanteria
            Paquete p = Buscar_mayor_prioridad(estanteria, cant_estanteria); // Busca y obtiene el paquete de mayor prioridad en la estanteria
            cant_estanteria--;  // Se reduce la cantidad de paquetes en la estanteria 
        signal(mutex_estanteria);  // Se desbloquea el mutex de la estanteria

        signal(sem_espacio_estanteria);  // Se da aviso de que hay espacio en la estanteria para el productor
      
        this_thread::sleep_for(chrono::milliseconds(420));  // Se espera 420ms simulando trafico o congestion

        wait(sem_espacio_cinta);  // Se espera a que haya espacio en la cinta

        wait(mutex_cinta); // Se bloquea el mutex de la cinta
            cinta.push(p);  // se coloca el paquete en la cinta
            cout << "Gestor colocó paquete ID=" << p.id                          //  Print para verificar los id de los paquetes (debugg principalmente) 
                 << " prioridad=" << p.prioridad << " en la cinta." << endl;     //  Print para ver que la prioridad sea la correcta (debugg principalmente) [de nuevo] 
        signal(mutex_cinta);  // Se desbloquea el mutex de la cinta

        signal(sem_cinta_llena);  // Se avisa de un nuevo paquete en la cinta para el consumidor

        procesados++;
    }
}
