// Arda Mavi - ardamavi.com

#ifndef FIL_H
#define  FIL_H

#include "Tas.h"

class Fil : public Tas{

    public:
        Fil(takim, int, int);

    bool yolKntrl(vector<Tas*>, pair <int, int>);

};

#endif
