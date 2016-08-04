// Arda Mavi - ardamavi.com

#ifndef VEZIR_H
#define VEZIR_H

#include "Tas.h"

class Vezir : public Tas{

    public:
        Vezir(takim, int, int);

    bool yolKntrl(vector<Tas*> , pair <int,  int>);

};

#endif
