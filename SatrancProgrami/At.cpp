// Arda Mavi - ardamavi.com

#include <iostream>
#include "Tas.h"
#include "At.h"

using namespace std;

        At::At(takim renk, int x, int y): Tas(renk, "At", x, y){}

    bool At::yolKntrl(vector<Tas*> taslar, pair <int, int> gidilecekyer){

        // Gittigi yerde tas olma :
        for(int i = 0; i < taslar.size(); i++){
            if(taslar[i]->getKonum() == this->getKonum()){
                continue;
            }
            if(taslar[i]->getKonum() == gidilecekyer) {
                if(taslar[i]->getTakim() == this->getTakim()){
                    return false;
                }
            }
        }

        // Kendi yerine oynayamaz :
        if(this->getKonum() == gidilecekyer){
            return false;
        }

        // Oynanabilecek yerler :
        if(make_pair(this->getKonum().first-2,this->getKonum().second-1) == gidilecekyer){
            return true;
        } else if(make_pair(this->getKonum().first-2,this->getKonum().second+1) == gidilecekyer){
            return true;
        } else if(make_pair(this->getKonum().first-1,this->getKonum().second-2) == gidilecekyer){
            return true;
        }else if(make_pair(this->getKonum().first-1,this->getKonum().second+2) == gidilecekyer){
            return true;
        }else if(make_pair(this->getKonum().first+1,this->getKonum().second-2) == gidilecekyer){
            return true;
        }else if(make_pair(this->getKonum().first+1,this->getKonum().second+2) == gidilecekyer){
            return true;
        }else if(make_pair(this->getKonum().first+2,this->getKonum().second-1) == gidilecekyer){
            return true;
        }else if(make_pair(this->getKonum().first+2,this->getKonum().second+1) == gidilecekyer){
            return true;
        } else{
            return false;
        }
    }
