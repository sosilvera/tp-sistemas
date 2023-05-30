#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <pthread.h>

#include "CargarArchivos.hpp"

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        // Completar (Ejercicio 4)
        hashMap.incrementar(palabraActual); // si no esta definida, la agrega
        cant++;
    }
    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}

void auxiliar(HashMapConcurrente &hashMap, std::vector<std::string> &filePaths, atomic<int> &prox_archivo) {
    unsigned int actual = prox_archivo.fetch_add(1);
    while (actual < filePaths.size()) {
        cargarArchivo(hashMap,filePaths[actual]);
        actual = prox_archivo.fetch_add(1);
    }
}

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {
    // Completar (Ejercicio 4)
    vector<thread> threads;
    atomic<int> prox_archivo(0);
    
    for (unsigned int i = 0; i < cantThreads; ++i) {
        threads.emplace_back(auxiliar,ref(hashMap),ref(filePaths),ref(prox_archivo));
    }

    for(auto& t : threads) {
        t.join();
    }
}

#endif
