// Arda Mavi - ardamavi.com

#ifndef KALE_H
#define  KALE_H

#include "Tas.h"

class Kale: public Tas{

    public:
        Kale(takim, int, int);

    bool yolKntrl(vector<Tas*>, pair <int, int>);
};

#endif
