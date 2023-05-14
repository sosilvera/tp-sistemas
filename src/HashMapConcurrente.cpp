#ifndef CHM_CPP
#define CHM_CPP

#include <iostream>
#include <fstream>
#include <pthread.h>

#include "HashMapConcurrente.hpp"

HashMapConcurrente::HashMapConcurrente(){
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    // Completar (Ejercicio 2)

    /*
    si puedo:       // puedo = hay algun incrementar ejecutandose || ni inc ni max se estan ejecutando
        incremento contador
        le doy permiso al siguiente incrementar
    si no puedo:
        wait al max
    */

    int key = hashIndex(clave);
    _mtx_claves[key].lock();

    auto it = tabla[key]->crearIt();
    bool encontre = false;

    while(it.haySiguiente() && !encontre) {
        string clave_actual = it.siguiente().first;
        if (clave == clave_actual)
            encontre = true;
        else 
            it.avanzar();
    }

    if (encontre) 
        it.siguiente().second++;
    else
        tabla[key]->insertar(make_pair(clave,1));
    
    _mtx_claves[key].unlock();
}

std::vector<std::string> HashMapConcurrente::claves() {
    // Completar (Ejercicio 2)

    // falta ver si agregan claves después de que ya las recorrí
    vector<string> res;
    for (int i = 0 ; i < cantLetras; ++i) {
        auto it = tabla[i]->crearIt();
        while (it.haySiguiente()) {
            res.push_back(it.siguiente().first);
            it.avanzar();
        }
    }

    return res;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    // Completar (Ejercicio 2)
    auto it = tabla[hashIndex(clave)]->crearIt();

    while(it.haySiguiente()) {
        string clave_actual = it.siguiente().first;
        if (clave == clave_actual) 
            return it.siguiente().second;
        else 
            it.avanzar();
    }

    return 0;
    
}

hashMapPair HashMapConcurrente::maximo() {
    hashMapPair *max = new hashMapPair();
    max->second = 0;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (
            auto it = tabla[index]->crearIt();
            it.haySiguiente();
            it.avanzar()
        ) {
            if (it.siguiente().second > max->second) {
                max->first = it.siguiente().first;
                max->second = it.siguiente().second;
            }
        }
    }

    return *max;
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cantThreads) {
    // Completar (Ejercicio 3)
}

#endif
