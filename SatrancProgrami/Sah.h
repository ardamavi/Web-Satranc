// Arda Mavi - ardamavi.com

#ifndef SAH_H
#define SAH_H

#include "Tas.h"

class Sah : public Tas{

    public:
    Sah(takim, int, int);

    double mesafeKare(pair <int, int> , pair <int, int>);

    bool sahaYakinMi(vector<Tas*>, pair <int, int>);

    bool yolKntrl(vector<Tas*>, pair <int, int>);

};

#endif
