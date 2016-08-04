// Arda Mavi - ardamavi.com

#ifndef TAHTA_H
#define TAHTA_H

#include "Tas.h"
#include <utility>

const string KISA_ROK = "kısa rok";
const string UZUN_ROK = "uzun rok";

class Tahta {
    private:
        string tahta[8][8];
        vector <Tas*> taslar;

        // 50 hamle kuralı icin :
        int geriSayim;

        // En passant kuralı için :
        pair<pair<int, int>, takim> gecerkenAlma;

    public:

    // First: Kısa && Second: Uzun
    pair<bool, bool> beyazRok;

    pair<bool, bool> siyahRok;

    Tahta();

    void tahtaSil();

    void tahtaCiz();

    vector<Tas*>* getTaslar();

    void tasEkle(Tas* tas);

    void setTaslar(vector<Tas*>);

    bool tasHareket(pair<int, int>, int, bool, int);

    bool hareketEt(string, pair <int, int> , pair <int, int>);

    pair<int, int> rakipTakimSahKonum(takim);

    int rakipTakimSahSira(takim);

    pair<bool, int> tehditVarMi(pair<int, int>, takim);

    bool sahMatMi(takim, int);

    bool sahVarMi(takim);

    bool rokYapma(string, string);

    bool karsilastir(string, string, int);

    bool patMi(takim);

    int getGeriSayim();

    void setGeriSayim(int);

    pair<pair<int, int>, takim> getGecerkenAlma();

    void setGecerkenAlma(pair<int, int>, takim);

    // OS Adını döner :
    string getOsAdi();

};

#endif
