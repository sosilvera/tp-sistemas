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
    _contador_inc = 0;
}

HashMapConcurrente::HashMapConcurrente(HashMapConcurrente &&h) : _mtx_claves(), _mtx(), _lightswitch() 
{
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
    _contador_inc = 0;
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    // Completar (Ejercicio 2)

    _mtx.lock();
    _contador_inc++;
    if(_contador_inc == 1) // el primero en entrar, prende la luz
        _lightswitch.lock();
    _mtx.unlock();

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

    _mtx.lock();
    _contador_inc--;
    if(_contador_inc == 0) // ultimo en salir, habilita la entrada
        _lightswitch.unlock();
    _mtx.unlock();
}

std::vector<std::string> HashMapConcurrente::claves() {
    // Completar (Ejercicio 2)
    vector<string> res;
    for (unsigned int i = 0 ; i < cantLetras; ++i) {
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

    _lightswitch.lock(); // si ve que hay alguien, no entra

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

    _lightswitch.unlock();

    // no destruimos el maximo ??

    return *max;
}

void HashMapConcurrente::auxiliar(hashMapPair &maximo_tot, atomic<int> &letra) {
    unsigned int actual = letra.fetch_add(1);
    while(actual < cantLetras) {

        hashMapPair max;
        max.second = 0;

        for (
            auto it = tabla[actual]->crearIt();
            it.haySiguiente();
            it.avanzar()
        ) {
            if (it.siguiente().second > max.second) {
                max.first = it.siguiente().first;
                max.second = it.siguiente().second;
            }
        }

        if (max.second > maximo_tot.second) {
            maximo_tot.first = max.first;
            maximo_tot.second = max.second;
        }

        actual = letra.fetch_add(1);
    }
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cantThreads) {
    // Completar (Ejercicio 3)

    vector<thread> threads;
    hashMapPair maximo;
    maximo.second = 0;
    atomic<int> letra(0);
    for (unsigned int i = 0; i < cantThreads; i++) {
        threads.emplace_back(&HashMapConcurrente::auxiliar,this,ref(maximo),ref(letra)); // cosas raras de c++
    }

    for (auto& t : threads) { 
        t.join();
    }

    return maximo;
}

#endif
