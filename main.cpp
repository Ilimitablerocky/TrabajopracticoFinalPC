#include "consumidor.h"
#include "productor.h"
#include "paquete.h"
#include "semaforo.h"
#include "gestor.h"

//LIMITES DEL SISTEMA
const int cantidad_Maxima_cinta = 5;

//VARIABLE productor/gestor
int cantidad_actual_estanteria = 0;
chrono::system_clock::time_point inicio_programa = chrono::system_clock::now();
int tiempo_espera_p1 = 0;
int tiempo_espera_p0 = 0;
int cant_producidos_p1 = 0;
int cant_producidos_p0 = 0;
int numero_paquete = 0;

std::mutex mutex_consola;
std::mutex mutex_idpaquete;

//ESTANTERIA...
Paquete estanteria[cantidad_Maxima_Estanteria];
std::mutex mutex_estanteria;
Semaforo sem_estanteria;

//CINTA...
std::queue<Paquete> cinta;
std::mutex mutex_cinta;
Semaforo sem_cinta;
Semaforo sem_espacio_cinta;

using namespace std;

void mostrarMetricas(int tp1, int tp0, int cantp1, int cantp0){
    cout << endl << "\t --------------------------- METRICAS ----------------------------" << endl;
    cout << "\t  CANTIDAD TOTAL DE PAQUETES PRODUCIDOS: " << cantp0 + cantp1 << endl;
    if(cantp0 == 0 && cantp1 == 0){
        cout << "\t  NO HUBO PRODUCCION POR LO TANTO NO HAY TIEMPOS DE ESPERA." << endl;
    }else{
        if(cantp0 == 0){
            cout << "\t  NO HUBO PAQUETES CON PRIORIDAD 0." << endl;
            cout << "\t  TIEMPO PROMEDIO DE ESPERA DE PAQUETES DE PRIORIDAD 1: " << (float)tp1 / cantp1 << "ms" << endl;
        }else{
            if(cant_producidos_p1 == 0){
                cout << "\t  TIEMPO PROMEDIO DE ESPERA DE PAQUETES DE PRIORIDAD 0: " << (float)tp0 / cantp0 << "ms" << endl;
                cout << "\t  NO HUBO PAQUETES CON PRIORIDAD 1." << endl;
            }else{
                cout << "\t  TIEMPO PROMEDIO DE ESPERA DE PAQUETES DE PRIORIDAD 0: " << (float)tp0 / cantp0 << "ms" << endl;
                cout << "\t  TIEMPO PROMEDIO DE ESPERA DE PAQUETES DE PRIORIDAD 1: " << (float)tp1 / cantp1 << "ms" << endl;
            }
        }
    }
}

int main() {
    /*
    // CONFIGURACION C - ESCENARIO PRUEBA DE CARGA MASIVA
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 1550);

    int cada_cuantos_paquetes = 500;

	//productor
    thread productor_1(productor, 1, 516, cada_cuantos_paquetes);
    thread productor_2(productor, 2, 517, cada_cuantos_paquetes);
    thread productor_3(productor, 3, 517, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 517);
    thread consumidor_2(consumidor, 2, 517);
    thread consumidor_3(consumidor, 3, 516);

    consumidor_1.join();
    consumidor_2.join();
    consumidor_3.join();
    productor_1.join();
    productor_2.join();
    productor_3.join();
    gestor_1.join();
    */


    /*
    // CONFIGURACION B - ESCENARIO PRUEBA DE CARGA MASIVA
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 1550);

    int cada_cuantos_paquetes = 500;

	//productor
    thread productor_1(productor, 1, 516, cada_cuantos_paquetes);
    thread productor_2(productor, 2, 517, cada_cuantos_paquetes);
    thread productor_3(productor, 3, 517, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 1550);

    consumidor_1.join();
    productor_1.join();
    productor_2.join();
    productor_3.join();
    gestor_1.join();
    */

    /*
    // CONFIGURACION A - ESCENARIO PRUEBA DE CARGA MASIVA
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 1550);

    int cada_cuantos_paquetes = 500;

	//productor
    thread productor_1(productor, 1, 1550, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 775);
    thread consumidor_2(consumidor, 2, 775);

    consumidor_1.join();
    consumidor_2.join();
    productor_1.join();
    gestor_1.join();
    */

    /*
    // CONFIGURACION C - ESCENARIO VACUIDAD
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 0);

    int cada_cuantos_paquetes = 500;

	//productor
    thread productor_1(productor, 1, 0, cada_cuantos_paquetes);
    thread productor_2(productor, 2, 0, cada_cuantos_paquetes);
    thread productor_3(productor, 3, 0, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 0);
    thread consumidor_2(consumidor, 2, 0);
    thread consumidor_3(consumidor, 3, 0);

    consumidor_1.join();
    consumidor_2.join();
    consumidor_3.join();
    productor_1.join();
    productor_2.join();
    productor_3.join();
    gestor_1.join();
    */


    /*
    // CONFIGURACION B - ESCENARIO VACUIDAD
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 0);

    int cada_cuantos_paquetes = 500;

	//productor
    thread productor_1(productor, 1, 0, cada_cuantos_paquetes);
    thread productor_2(productor, 2, 0, cada_cuantos_paquetes);
    thread productor_3(productor, 3, 0, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 0);

    consumidor_1.join();
    productor_1.join();
    productor_2.join();
    productor_3.join();
    gestor_1.join();
    */

    /*
    // CONFIGURACION A - ESCENARIO VACUIDAD
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 0);

    int cada_cuantos_paquetes = 500;

	//productor
    thread productor_1(productor, 1, 0, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 0);
    thread consumidor_2(consumidor, 2, 0);

    consumidor_1.join();
    consumidor_2.join();
    productor_1.join();
    gestor_1.join();
    */

    /*
    // CONFIGURACION C - ESCENARIO SATURACION DE RECURSOS
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 8);

    int cada_cuantos_paquetes = 0;

	//productor
    thread productor_1(productor, 1, 2, cada_cuantos_paquetes);
    thread productor_2(productor, 2, 3, cada_cuantos_paquetes);
    thread productor_3(productor, 3, 3, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 2);
    thread consumidor_2(consumidor, 2, 3);
    thread consumidor_3(consumidor, 3, 3);

    consumidor_1.join();
    consumidor_2.join();
    consumidor_3.join();
    productor_1.join();
    productor_2.join();
    productor_3.join();
    gestor_1.join();
    */


    /*
    // CONFIGURACION B - ESCENARIO SATURACION DE RECURSOS
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 8);

    int cada_cuantos_paquetes = 0;

	//productor
    thread productor_1(productor, 1, 3, cada_cuantos_paquetes);
    thread productor_2(productor, 2, 3, cada_cuantos_paquetes);
    thread productor_3(productor, 3, 2, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 8);

    consumidor_1.join();
    productor_1.join();
    productor_2.join();
    productor_3.join();
    gestor_1.join();
    */

    /*
    // CONFIGURACION A - ESCENARIO SATURACION DE RECURSOS
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 8);

    int cada_cuantos_paquetes = 0;

	//productor
    thread productor_1(productor, 1, 8, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 4);
    thread consumidor_2(consumidor, 2, 4);

    consumidor_1.join();
    consumidor_2.join();
    productor_1.join();
    gestor_1.join();
    */

    /*
    // CONFIGURACION C - ESCENARIO EQUIDAD
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 20);

    int cada_cuantos_paquetes = 12;

	//productor
    thread productor_1(productor, 1, 6, cada_cuantos_paquetes);
    thread productor_2(productor, 2, 7, cada_cuantos_paquetes);
    thread productor_3(productor, 3, 7, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 6);
    thread consumidor_2(consumidor, 2, 7);
    thread consumidor_3(consumidor, 3, 7);

    consumidor_1.join();
    consumidor_2.join();
    consumidor_3.join();
    productor_1.join();
    productor_2.join();
    productor_3.join();
    gestor_1.join();
    */


    /*
    // CONFIGURACION B - ESCENARIO EQUIDAD
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 20);

    int cada_cuantos_paquetes = 12;

	//productor
    thread productor_1(productor, 1, 6, cada_cuantos_paquetes);
    thread productor_2(productor, 2, 7, cada_cuantos_paquetes);
    thread productor_3(productor, 3, 7, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 20);

    consumidor_1.join();
    productor_1.join();
    productor_2.join();
    productor_3.join();
    gestor_1.join();
    */

    /*
    // CONFIGURACION A - ESCENARIO EQUIDAD
    init(sem_estanteria, 0);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    // gestor
    thread gestor_1(gestor, 20);

    int cada_cuantos_paquetes = 12;

	//productor
    thread productor_1(productor, 1, 20, cada_cuantos_paquetes);

    thread consumidor_1(consumidor, 1, 10);
    thread consumidor_2(consumidor, 2, 10);

    consumidor_1.join();
    consumidor_2.join();
    productor_1.join();
    gestor_1.join();
    */

    mostrarMetricas(tiempo_espera_p1, tiempo_espera_p0, cant_producidos_p1, cant_producidos_p0);

    return 0;
}
