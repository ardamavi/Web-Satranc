// Arda Mavi - ardamavi.com

#include <iostream>
#include "Tas.h"
#include "Piyon.h"
#include "Tahta.h"

using namespace std;

Piyon::Piyon(takim renk, int x, int y) : Tas(renk, "Piyon", x, y){}

bool Piyon::vezirOlsunMu(takim renk,pair <int, int> gidilecekYer){

    if(renk == beyaz){
        // Tasin rengi beyaz ise:
        if(gidilecekYer.first == 7){
            return true;
        } else{
            return false;
        }
    }else{
        // Tasin rengi siyah ise:
        if(gidilecekYer.first == 0){
            return true;
        } else{
            return false;
        }
    }

}

bool Piyon::yolKntrl(vector<Tas*> taslar, pair<int, int> gidilecekYer, Tahta tahta){
    // benim konumum this->konum
    //taslar[i].konum

    if(this->getKonum() == gidilecekYer){
        return false;
    }

    int yon;
    int baslamaYeri;

    if (this->getTakim() == beyaz)
    {
        yon = 1;
        baslamaYeri = 1;
    }
    else{
        yon = -1;
        baslamaYeri = 6;
    }

    // Geri gidemez :
    if(yon == 1 && this->getKonum().first > gidilecekYer.first){
        return false;
    } else if(yon == -1 && this->getKonum().first < gidilecekYer.first){
        return false;
    }

    if(( gidilecekYer != make_pair(this->getKonum().first+ (1 * yon), this->getKonum().second))
       && !((gidilecekYer == make_pair(this->getKonum().first+ (2 * yon), this->getKonum().second)) && this->getKonum().first == baslamaYeri)
       && (gidilecekYer != make_pair(this->getKonum().first+ (1 * yon), this->getKonum().second- (1 * yon)))
       && (gidilecekYer != make_pair(this->getKonum().first+ (1 * yon), this->getKonum().second+ (1 * yon)))){
        return false;
    }

    int ileriLimiti = 1;
    // Piyon başlama yerindeyse
    if(this->getKonum().first == baslamaYeri){
        ileriLimiti = 2;
    }
    int mesafe = (gidilecekYer.first - this->getKonum().first) * yon;

    if (ileriLimiti < mesafe)
    {
        return false;
    }

    // İleri gidiliyorsa :
    if(gidilecekYer.second == this->getKonum().second) {

        for (int i = 0; i < taslar.size(); i++) {
            if (taslar[i]->getKonum() == this->getKonum()) {
                continue;
            }
            if (taslar[i]->getKonum() ==
                              make_pair(this->getKonum().first + (1 * yon), this->getKonum().second)) {
                return false;
            }
            if (mesafe > 1 && taslar[i]->getKonum() ==
                              make_pair(this->getKonum().first + (2 * yon), this->getKonum().second)) {
                return false;
            }
        }
    }

    // Capraz gidiyorsa
    if(gidilecekYer == make_pair(this->getKonum().first+ (1 * yon), this->getKonum().second- (1 * yon))){

        // Eger caprazi doluysa:
        for (int i = 0; i < taslar.size(); i++) {
            if(taslar[i]->getKonum() == this->getKonum()){
                continue;
            }
            if(taslar[i]->getKonum() == make_pair(this->getKonum().first+ (1 * yon), this->getKonum().second- (1 * yon))){
                if (taslar[i]->getTakim() == this->getTakim()) {
                    return false;
                }
                else {
                    return true;
                }
            }
        }
        if(tahta.getGecerkenAlma().second == yok){
          return false;
        }
        else if (tahta.getGecerkenAlma().second == this->getTakim())
        {
          return false;
        }

    } else if(gidilecekYer == make_pair(this->getKonum().first+ (1 * yon), this->getKonum().second+ (1 * yon))){
        // Eger çaprazi doluysa:
        for (int i = 0; i < taslar.size(); i++) {
            if(taslar[i]->getKonum() == this->getKonum()){
                continue;
            }
            if(taslar[i]->getKonum() == make_pair(this->getKonum().first+ (1 * yon), this->getKonum().second+ (1 * yon))){
                if (taslar[i]->getTakim() == this->getTakim()) {
                    return false;
                }
                else{
                    return true;
                }
            }
        }
        if(tahta.getGecerkenAlma().second == yok){
          return false;
        }
        else if (tahta.getGecerkenAlma().second == this->getTakim())
        {
          return false;
        }

    }

    // Piyon belirtilen konuma gidebilir mi?
    // 1. Piyon baslangic satirindaysa ve onu bos ise 1 veya 2 adim onune gidebilir.
    // 2. Piyon baslangic satirinda degilse ve onu bos ise 1 adim onune gidebilir.
    // 3. Piyon caprazinda rakip tas var ise, capraz onune gidebilir.

    return true;
}
