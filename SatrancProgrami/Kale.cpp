// Arda Mavi - ardamavi.com

#include <iostream>
#include "Tas.h"
#include "Kale.h"

using namespace std;

Kale::Kale(takim renk, int x, int y) : Tas(renk, "Kale", x, y){}

bool Kale::yolKntrl(vector<Tas*> taslar, pair <int, int> gidilecekyer){
    // Kendi Yerine oynayamaz :
    if(this->getKonum() == gidilecekyer){
        return false;
    }
    // Kale Kurallari:

    // 1. Sag sola gidebilir.
    // 2. Yukari asagi gidebilir.

    // Gidecegi yerle arasinda tas varsa false doner.

    // Ta ki onune biri cikana kadar :
        // Onune cikan farkli renkse yer.
        // Ayni renkse gidemez.

    // Sag sol ve asagi yukari kontrol :
    if(!(gidilecekyer.first == this->getKonum().first || gidilecekyer.second == this->getKonum().second)) {
        return false;
    }

    // Gidecegi yerle arasinda tas varsa false doner:

    if(gidilecekyer.first == this->getKonum().first){
        // Sag sol giderse:    (Y ekseni degisir)

        for (int i = 0; i < taslar.size(); i++) {
            if(taslar[i]->getKonum() == this->getKonum()){
                continue;
            }

            if(gidilecekyer.second < this->getKonum().second){
                // Sola Hareket:

                if(taslar[i]->getKonum().first == this->getKonum().first && taslar[i]->getKonum().second < this->getKonum().second){
                    // Tasimizin solunda :

                    if(gidilecekyer.second < taslar[i]->getKonum().second){
                        // Tas yoluna cikti :
                        return false;
                    }

                }

            } else{
                // Sag hareket :

                if(taslar[i]->getKonum().first == this->getKonum().first && taslar[i]->getKonum().second > this->getKonum().second){
                    // Tasimizin saginda :

                    if(gidilecekyer.second > taslar[i]->getKonum().second){
                        // Tas yoluna cikti :
                        return false;
                    }

                }

            }
        }

    }else if(gidilecekyer.second == this->getKonum().second){
        // Yukari asagi giderse : (X ekseni degisir)

        for (int i = 0; i < taslar.size(); i++) {
            if(taslar[i]->getKonum() == this->getKonum()){
                continue;
            }

            if(gidilecekyer.first < this->getKonum().first){
                // yukari Hareket:

                if(taslar[i]->getKonum().first > gidilecekyer.first
                   && taslar[i]->getKonum().second == gidilecekyer.second
                   && this->getKonum().first > taslar[i]->getKonum().first){
                    // Onumuze cikti :
                    return false;
                }
                }else{
                // asagi hareket :

                if(taslar[i]->getKonum().first < gidilecekyer.first
                   && taslar[i]->getKonum().first > this->getKonum().first
                   && gidilecekyer.second == taslar[i]->getKonum().second){
                    // Onumuze cikti :
                    return false;
                }
            }
        }
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

    return true;
}
