#include "consumidor.h"

void consumidor(int id_consumidor, int paquetes_x_consumidores){ // consumidor se ingresa el id y la cantidad de paquete x consumidor
	for(int f = 0; f < paquetes_x_consumidores; f++){
        wait(sem_cinta); // esperamos el paquete en la cinta, sino a dormir
        Paquete p;
        int x = 0;
        while(x == 0){
            mutex_cinta.lock(); //bloqueamos la cinta
            p = cinta.front(); // miramos el primer paquete

            auto actual = std::chrono::system_clock::now(); // guardamos el tiempo actual

            // calculamos el tiempo del paquete en la cinta
            // devuelve un numero raro y lo casteamos a miliseugnos y sacamos un valor int
            auto diferencia = std::chrono::duration_cast<std::chrono::milliseconds>(actual-p.ingreso_cinta).count();

            if(diferencia >= 550){ //770 > 550 entramos, sino...
                cinta.pop(); // eliminamos el paquete de la cinta
                mutex_cinta.unlock(); // debloqueamos la cinta y
                signal(sem_espacio_cinta); // avisamos que hay lugar disponible
                x = 1; // sale del bucle while

            }else{ //esperamos a que cumpla el tiempo requerido en la cinta..
                auto falta = 550 - diferencia; //hacemos una cuenta 550 - 230 = falta(320)
                mutex_cinta.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(falta)); // esperamos los 320 ms y volvemos al principio
            }
        }
        std::cout << "Consumidor: " << id_consumidor << " Finalizo paquete: " <<p.id  << std::endl;

        // Debe existir un retardo de 270ms entre cada liberación de paquete.
        std::this_thread::sleep_for(std::chrono::milliseconds(270));
	}
}
