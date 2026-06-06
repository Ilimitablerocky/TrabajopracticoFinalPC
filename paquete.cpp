#include "paquete.h"

void Crear_Paquete(Paquete& p, int nro, int prioridad){
    p.id = nro;
    p.prioridad = prioridad;
    p.creacion = std::chrono::systemclock::now();
}

void mostrar_Paquete(Paquete& p){
    std::cout << "Paquete: " << p.id << std::endl;
    std::cout << "Prioridad: " << p.prioridad << std::endl;
    std::cout << "Fecha Creacion: " << "FECHA_DE_CREACION" << std::endl;
}

Paquete buscar_mayor_prioridad(Paquete vec[], int cantidad_estanteria){
    auto ahora = std::chrono::system_clock::now();                       //el tiempo transcurrido hasta el momento

    for(int i = 0; i < cantidad_estanteria; i++){                        //primero verifica si pasó más de 6 segundos para los paquetes de prioridad baja
        if(vec[i].prioridad == 0){
            auto espera = std::chrono::duration_cast<std::chrono::milliseconds>(ahora - vec[i].creacion).count(); //diferencia de tiempo entre el momento y la creacion del paquete
            if(espera >= 6000){
                Paquete p = vec[i];
                for(int j = i; j < cantidad_estanteria - 1; j++){         //barre el arreglo para pisar el dato que se sacó
                    vec[j] = vec [j+1];
                }
                return p;
            }
        }
    }

    for(int i = 0; i < cantidad_estanteria; i++){                         //paquetes de prioridad alta
        if(vec[i].prioridad == 1){
            Paquete p = vec[i];
            for(int j = i; j < cantidad_estanteria - 1; j++){
                    vec[j] = vec [j+1];
            }
            return p;
        }
    }

    for(int i = 0; i < cantidad_estanteria; i++){                         //si solo hay un paquete en la estantería o si solo hay paquetes de prioridad baja
        if(cantidad_estanteria == 1){
            Paquete p = vec[0];
            return p;
        } else {
            Paquete p = vec[i];
            for(int j = i; j < cantidad_estanteria - 1; j++){
                    vec[j] = vec [j+1];
            }
            return p;
        }
    }
}
