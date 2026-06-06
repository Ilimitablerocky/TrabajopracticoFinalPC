#include "consumidor.h"
#include "productor.h"
#include "paquete.h"
#include "semaforo.h"
#include "gestor.h"

//LIMITES DEL SISTEMA
const int cantidad_Maxima_Paquetes = 1550;
const int cantidad_Maxima_Estanteria = 100;
const int cantidad_Maxima_cinta = 5;
const int frecuencia_prioridad_0 = 20;          //cada cuantos paquetes se crea un paquete con prioridad 0

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
Semaforo sem_espacio_estanteria;

//CINTA...
std::queue<Paquete> cinta;
std::mutex mutex_cinta;
Semaforo sem_cinta;
Semaforo sem_espacio_cinta;

using namespace std;

int main() {
    //SEMAFOROS
    //ESTANTERIA
    init(sem_estanteria, 0);
    init(sem_espacio_estanteria, cantidad_Maxima_Estanteria);
    //CINTA
    init(sem_cinta, 0);
    init(sem_espacio_cinta, cantidad_Maxima_cinta);

    //productor
    int cantidad_productores = 1;
    int paquetes_x_productor = cantidad_Maxima_Paquetes / cantidad_productores;
    //int resto1 = cantidad_Maxima_Paquetes % cantidad_productores;

    // gestor
    thread gestor_1(gestor);

	//productor
    thread productor_1(productor, 1, paquetes_x_productor);
    //thread productor_2(productor, 2, paquetes_x_productor);
    //thread productor_3(productor, 3, paquetes_x_productor + resto1);

    //consumidor 1550/3 = 516 resto = 2 quien lo trabaja?
    int cantidad_consumidores = 1;
    int paquetes_x_consumidor = cantidad_Maxima_Paquetes / cantidad_consumidores;
    //int resto = cantidad_Maxima_Paquetes % cantidad_consumidores;

    thread consumidor_1(consumidor, 1, paquetes_x_consumidor);
    //thread consumidor_2(consumidor, 2, paquetes_x_consumidor);
    //thread consumidor_3(consumidor, 3, paquetes_x_consumidor + resto);

    consumidor_1.join();
    //consumidor_2.join();
    //consumidor_3.join();
    productor_1.join();
    //productor_2.join();
    //productor_3.join();
    gestor_1.join();

	cout << endl << "\t --------------------------- METRICAS ----------------------------" << endl;
    cout << "\t  CANTIDAD TOTAL DE PAQUETES PRODUCIDOS: " << cant_producidos_p0 + cant_producidos_p1 << endl;
    cout << "\t  TIEMPO PROMEDIO DE ESPERA DE PAQUETES DE PRIORIDAD 0: " << (float)tiempo_espera_p0 / cant_producidos_p0 << "ms" << endl;
    cout << "\t  TIEMPO PROMEDIO DE ESPERA DE PAQUETES DE PRIORIDAD 1: " << (float)tiempo_espera_p1 / cant_producidos_p1 << "ms" << endl;

    return 0;
}
