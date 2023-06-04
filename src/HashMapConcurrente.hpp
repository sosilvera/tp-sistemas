#ifndef HMC_HPP
#define HMC_HPP

#include <atomic>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <semaphore.h>

#include "ListaAtomica.hpp"

typedef std::pair<std::string, unsigned int> hashMapPair;

using namespace std;

class HashMapConcurrente {
 public:
    static const unsigned int cantLetras = 26;

    HashMapConcurrente();
    HashMapConcurrente(HashMapConcurrente&& h);

    ~HashMapConcurrente();

    void incrementar(std::string clave);
    std::vector<std::string> claves();
    unsigned int valor(std::string clave);

    hashMapPair maximo();
    hashMapPair maximoParalelo(unsigned int cantThreads);

 private:
    ListaAtomica<hashMapPair> *tabla[HashMapConcurrente::cantLetras];

    static unsigned int hashIndex(std::string clave);

    void auxiliar(hashMapPair &maximo_tot, atomic<int> &letra);

    mutex _mtx_claves[HashMapConcurrente::cantLetras];

    mutex _mtx; 
    mutex _lightswitch; 
    int _contador_inc;

    mutex _mtx_max;
};

#endif  /* HMC_HPP */
