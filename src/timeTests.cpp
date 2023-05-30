#include <iostream>
#include <time.h>

#include "HashMapConcurrente.hpp"
#include "CargarArchivos.hpp"

#define BILLION  1000000000L;

double medir(struct timespec &start, struct timespec &stop) {
    double res = (stop.tv_sec - start.tv_sec) + (double)( stop.tv_nsec - start.tv_nsec ) / (double)BILLION;
    return res;
}

int main(int argc, char **argv) {
    if (argc < 4) {
        std::cout << "Error: faltan argumentos." << std::endl;
        std::cout << std::endl;
        std::cout << "Modo de uso: " << argv[0] << " <threads_lectura> <threads_maximo>" << std::endl;
        std::cout << "    " << "<archivo1> [<archivo2>...]" << std::endl;
        std::cout << std::endl;
        std::cout << "    threads_lectura: "
            << "Cantidad de threads a usar para leer archivos." << std::endl;
        std::cout << "    threads_maximo: "
            << "Cantidad de threads a usar para computar máximo." << std::endl;
        std::cout << "    archivo1, archivo2...: "
            << "Archivos a procesar." << std::endl;
        return 1;
    }
    int cantThreadsLectura = std::stoi(argv[1]);
    int cantThreadsMaximo = std::stoi(argv[2]);

    std::vector<std::string> filePaths = {};
    for (int i = 3; i < argc; i++) {
        filePaths.push_back(argv[i]);
    }

    HashMapConcurrente hashMap = HashMapConcurrente();
    cargarMultiplesArchivos(hashMap, cantThreadsLectura, filePaths);

    // medimos tiempos
    struct timespec start, stop; // estructuras que guardan los timestamps

    clock_gettime(CLOCK_REALTIME,&start); // tomamos tiempo cuando empieza
    auto maximo = hashMap.maximoParalelo(cantThreadsMaximo);
    clock_gettime(CLOCK_REALTIME,&stop); // tomamos tiempo cuando termina
    double tiempo = medir(start,stop);

    std::cout << "El máximo es: " << maximo.first << ", con " << maximo.second << " apariciones" << std::endl;
    
    std::cout << "Tardó: " << tiempo << "s" << std::endl;

    return 0;
}
