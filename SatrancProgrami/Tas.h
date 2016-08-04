// Arda Mavi - ardamavi.com

#ifndef TAS_H
#define TAS_H

#include <iostream>
#include <vector>

using namespace std;

enum takim{

    beyaz = 1,
    yok = 0,
    siyah = -1

};

class Tas{
    private:
        takim renk;
        string adi;
        pair <int, int> konum;

    public:


        Tas(takim, string, int, int);

        Tas(Tas &tas);

        string tasKisaltmasi();

        pair<int, int> getKonum();

        takim  getTakim();

        string getAdi();

        void setKonum(pair <int, int> );
};

#endif
