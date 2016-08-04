// Arda Mavi - ardamavi.com

#ifndef AT_H
#define AT_H

#include "Tas.h"

class At : public Tas {

    public:
        At(takim, int, int);

    bool yolKntrl(vector<Tas*>, pair <int, int>);

};


#endif
