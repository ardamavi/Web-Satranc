// Arda Mavi - ardamavi.com

#ifndef PIYON_H
#define PIYON_H

#include "Tas.h"
#include "Tahta.h"

class Piyon: public Tas{
    public:
        Piyon(takim, int , int );

        bool vezirOlsunMu(takim ,pair <int, int> );

        bool yolKntrl(vector<Tas*> , pair<int, int>, Tahta );
};

#endif
