// Arda Mavi - ardamavi.com

#include <iostream>
#include "Tas.h"
#include "Fil.h"
#include "Kale.h"
#include "Vezir.h"

using namespace std;

Vezir::Vezir(takim renk, int x, int y) : Tas(renk, "Vezir", x, y){}

// Kale ile filin özelliklerine sahiptir :
bool Vezir::yolKntrl(vector<Tas*> taslar, pair <int, int> gidilecekyer){
    return Kale(this->getTakim(), this->getKonum().first, this->getKonum().second).yolKntrl(taslar, gidilecekyer)
            || Fil(this->getTakim(), this->getKonum().first, this->getKonum().second).yolKntrl(taslar, gidilecekyer);
}
