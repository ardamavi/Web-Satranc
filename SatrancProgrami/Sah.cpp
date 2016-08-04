// Arda Mavi - ardamavi.com

#include <iostream>
#include "Tas.h"
#include "Sah.h"

using namespace std;

Sah::Sah(takim renk, int x, int y) : Tas(renk, "Sah", x, y){}

// Oynanacak yer ile su anki mesafenin karesini olcer: (Pisagor ucgeni)
double Sah::mesafeKare(pair <int, int> konum1, pair <int, int> konum2){

    double sonuc = (double)( ((konum2.first-konum1.first)*(konum2.first-konum1.first)) +
            ((konum2.second - konum1.second)*(konum2.second - konum1.second)) );

    return sonuc;
}

bool Sah::sahaYakinMi(vector<Tas*> taslar, pair <int, int> gidilecekyer){

    for (int i = 0; i < taslar.size(); i++) {
        // Tas Bizim Tas ise :
        if(taslar[i]->getKonum() == this->getKonum()){
            continue;
        }

        // Cevredeyse :
            for (int a = -1; a < 2; a++) {
                // Satir Kontrol :
                for (int b = -1; b < 2; b++) {
                    // Stun Kontrol :
                    if(taslar[i]->getKonum() == make_pair(gidilecekyer.first+a, gidilecekyer.second+b)){
                        if(taslar[i]->getAdi() == "Sah") {
                            return true;
                        }
                    }
                }
            }

    }

    return false; // Yakin degil.
}

bool Sah::yolKntrl(vector<Tas*> taslar, pair <int, int> gidilecekyer){

    // 1 adım oynar.
    // Baska saha en az 1 kare uzaklikta yaklasabilir.
    // Baska sahi yiyemez.

    // Kendi yerine oynayamaz:
    if(this->getKonum() == gidilecekyer){
        return false;
    }

    if(mesafeKare(this->getKonum(),gidilecekyer) > 2){
        return false;
    }

    // Gittigi yerde kendi takimi varsa false doner :
    for (int k = 0; k < taslar.size(); k++) {
        if(taslar[k]->getKonum() == this->getKonum()){
            continue;
        }
        if(taslar[k]->getKonum() == gidilecekyer) {
            if (this->getTakim() == taslar[k]->getTakim()){
                return false;
            }
        }
    }

    if(sahaYakinMi(taslar, gidilecekyer)){
        return false;
    }

    return true;
}
