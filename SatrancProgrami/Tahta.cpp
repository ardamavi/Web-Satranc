// Arda Mavi - ardamavi.com

#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include "Tas.h"
#include "Kale.h"
#include "At.h"
#include "Fil.h"
#include "Vezir.h"
#include "Piyon.h"
#include "Sah.h"
#include "Tahta.h"
#include "Color.h"


Color::Modifier color1(Color::BG_COLOR1);
Color::Modifier color2(Color::BG_COLOR2);
Color::Modifier cerceveColor(Color::BG_CERCEVE);
Color::Modifier tasBeyaz(Color::FG_TASBEYAZ);
Color::Modifier yaziBeyaz(Color::FG_BEYAZ);
Color::Modifier tasSiyah(Color::FG_TASSIYAH);
Color::Modifier defaultColor(Color::FG_DEFAULT);

using namespace std;


Tahta::Tahta(){

    // Rok durumları yapılabilir 'e ayarlanır :
    beyazRok = make_pair(true, true);
    siyahRok = make_pair(true, true);

    // 50 hamle kuralı için :
    this->geriSayim = 50;

    // Piyonlar tahta'daki konumlarına yerleştirilir :
    int satir = 1;
    takim renk = beyaz;
    for (int i = 0; i < 8; i++){
        Piyon* piyon = new Piyon(renk, satir, i);
        taslar.push_back(piyon);
        if (i == 7 && renk == beyaz){
            renk = siyah;
            satir = 6;
            i = -1;
        }
    }

    // Taslar tahta'daki konumlarına yerleştirilir :

    renk = beyaz;
    satir = 0;
    int sutun = 0;

    taslar.push_back(new Kale(renk, satir, sutun++));
    taslar.push_back(new At(renk, satir, sutun++));
    taslar.push_back(new Fil(renk, satir, sutun++));
    taslar.push_back(new Vezir(renk, satir, sutun++));
    taslar.push_back(new Sah(renk, satir, sutun++));
    taslar.push_back(new Fil(renk, satir, sutun++));
    taslar.push_back(new At(renk, satir, sutun++));
    taslar.push_back(new Kale(renk, satir, sutun++));


    renk = siyah;
    satir = 7;
    sutun = 0;
    taslar.push_back(new Kale(renk, satir, sutun++));
    taslar.push_back(new At(renk, satir, sutun++));
    taslar.push_back(new Fil(renk, satir, sutun++));
    taslar.push_back(new Vezir(renk, satir, sutun++));
    taslar.push_back(new Sah(renk, satir, sutun++));
    taslar.push_back(new Fil(renk, satir, sutun++));
    taslar.push_back(new At(renk, satir, sutun++));
    taslar.push_back(new Kale(renk, satir, sutun++));

}

// Tahta temizlenir :
void Tahta::tahtaSil(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            tahta[i][j] = "   ";
        }
    }
}

// Tahta çizilir :
void Tahta::tahtaCiz(){
    tahtaSil();
    for (int i = 0; i < taslar.size(); i++){
        Tas* tas = taslar[i];
        tahta[tas->getKonum().first][tas->getKonum().second] = (tas->tasKisaltmasi());
    }
    // Çerçeve yazdırılır :
    string cerceve = "    A  B  C  D  E  F  G  H    ";
    cout << cerceveColor << yaziBeyaz << cerceve << endl;

    // Tahta çizilir :
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if (j == 0){
                cout << yaziBeyaz << " " << cerceveColor << i + 1 << " ";
            }
            if(j%2 == 0){
              if(i%2 == 0){
                cout << color1;
              }else{
                cout << color2;
              }
            }else{
              if(i%2 != 0){
                cout << color1;
              }else{
                cout << color2;
              }
            }

            if(tahta[i][j] != "   "){

              for (int c = 0; c < taslar.size(); c++) {
                if(taslar[c]->getKonum() == make_pair(i, j)){
                  if(taslar[c]->getTakim() == siyah){
                    // Beyaz ise :
                      cout << tasSiyah << tahta[i][j] ;
                  }else{
                    // Siyah ise :
                      cout << tasBeyaz << tahta[i][j] ;
                  }
                }
              }

            }else{
              cout << tahta[i][j] ;
            }

            if (j == 7){
                cout << yaziBeyaz << cerceveColor << " " << i + 1 << " ";
            }
        }
        cout << endl;
    }
    cout << yaziBeyaz << cerceveColor << cerceve << endl;
}

// Taslar pointer vektörünü döner :
vector<Tas*>* Tahta::getTaslar(){
return &(this->taslar);
}

// Tahtaya taş eklememizi sağlar :
void Tahta::tasEkle(Tas* tas){
this->taslar.push_back(tas);
}

// Tahtaya çizilecek tasları ayarlar :
void Tahta::setTaslar(vector<Tas*> gelenTaslar){
  for (int i = 0; i < this->taslar.size(); i++)
  {
    delete(this->taslar[i]);
  }
  this->taslar.clear();
  for (int i = 0; i < gelenTaslar.size(); i++) {
    this->taslar.push_back(new Tas(*(gelenTaslar[i])));
  }
}

// Taşı hareket ettirir :
bool Tahta::tasHareket(pair<int, int> gidilecekYer, int rakipTasSira, bool rakiptasVarMi, int tasSira){
this->taslar[tasSira]->setKonum(gidilecekYer);
// Burada rakip tas var ise, tas yenir(silinir) :
  if(rakiptasVarMi){
    this->taslar.erase(this->taslar.begin() + rakipTasSira);
  }
return true;
}

// hareket edildi : true
// 1. Verilen konumdaki tası bul
// 2. Tasin turunu ismine bakarak bul ve casting yap
// 3. Tasın gidilecekyere gidip gidemeyecegine bak.
// 4. Gidebiliyorsa konumunu guncelle.
// 5. Eger gittigi yerde baska bir rakip tas varsa, onu yok et.
bool Tahta::hareketEt(string oyuncuSirasi, pair <int, int> tasKonum, pair <int, int> gidilecekYer){

  if(gidilecekYer.first<0 || gidilecekYer.first>7 || gidilecekYer.second<0 || gidilecekYer.second>7){
    // Tahtanın sınırlarının içindeyse
    return false;
  }

int tasSira;

// Oynayan taş oynaması gereken takımda değil ise hata verir :
for (int i = 0; i < this->taslar.size(); i++) {
    if(this->taslar[i]->getKonum() == tasKonum){
        tasSira = i;
        if(taslar[i]->getTakim() == beyaz && oyuncuSirasi != "Beyaz"){
          return false;
        }else if(taslar[i]->getTakim() == siyah && oyuncuSirasi != "Siyah"){
          return false;
        }
        break;
    }else if(i == (this->taslar.size()-1)){
      // Belirlenen konumda tas yok :
      return false;
    }
}

int rakipTasSira;
bool rakiptasVarMi = false;

// Rakip taş var mı diye bakılır:
for (int j = 0; j < this->taslar.size(); j++) {
    if(this->taslar[j]->getKonum() == gidilecekYer){
        rakiptasVarMi = true;
        rakipTasSira = j;
        break;
    }
}

// Casting yapılır :
if(this->taslar[tasSira]->getAdi() == "Piyon"){
  if (((Piyon*)this->taslar[tasSira])->yolKntrl(this->taslar, gidilecekYer, *this)) {
    // Piyon kurallarına uygunsa hareket edilir :
     this->tasHareket(gidilecekYer,rakipTasSira,rakiptasVarMi,tasSira);
     if (((Piyon*)this->taslar[tasSira])->vezirOlsunMu(this->taslar[tasSira]->getTakim(), gidilecekYer)){
       // Eğer piyon vezir olacaksa :
       // Vezir taslara eklenir
       this->taslar.push_back(new Vezir(this->taslar[tasSira]->getTakim(), this->taslar[tasSira]->getKonum().first, this->taslar[tasSira]->getKonum().second));

       // Piyon silinir :
       delete(this->taslar[tasSira]);
       this->taslar.erase(this->taslar.begin()+tasSira);
     }
     return true;
  }
}else if(taslar[tasSira]->getAdi() == "Kale"){
  if (((Kale*)this->taslar[tasSira])->yolKntrl(this->taslar, gidilecekYer)) {
    // Kale kurallarına uygunsa hareket edilir :

    // Kale hareket ettiği için ileride rok yapamaz:
    if(this->taslar[tasSira]->getTakim() == beyaz){
      if(this->taslar[tasSira]->getKonum().second == 0){
        // Soldaki
        beyazRok.second = false;
      }else{
        // Sağdaki
        beyazRok.first = false;
      }
    }else if(this->taslar[tasSira]->getTakim() == siyah){
      if(this->taslar[tasSira]->getKonum().second == 0){
        // Soldaki
        siyahRok.second = false;
      }else{
        // Sağdaki
        siyahRok.first = false;
      }
    }

      return this->tasHareket(gidilecekYer,rakipTasSira,rakiptasVarMi,tasSira);
  }
}else if(taslar[tasSira]->getAdi() == "At"){
  if (((At*)this->taslar[tasSira])->yolKntrl(this->taslar, gidilecekYer)) {
      // Atkurallarına uygunsa hareket edilir :
      return this->tasHareket(gidilecekYer,rakipTasSira,rakiptasVarMi,tasSira);
  }
}else if(taslar[tasSira]->getAdi() == "Fil"){
  if (((Fil*)this->taslar[tasSira])->yolKntrl(this->taslar, gidilecekYer)) {
      // Fil kurallarına uygunsa hareket edilir :
      return this->tasHareket(gidilecekYer,rakipTasSira,rakiptasVarMi,tasSira);
  }
}else if(taslar[tasSira]->getAdi() == "Vezir"){
  if (((Vezir*)this->taslar[tasSira])->yolKntrl(this->taslar, gidilecekYer)) {
      // Vezir kurallarına uygunsa hareket edilir :
      return this->tasHareket(gidilecekYer,rakipTasSira,rakiptasVarMi,tasSira);
  }
}else if(taslar[tasSira]->getAdi() == "Sah"){
  if (((Sah*)this->taslar[tasSira])->yolKntrl(this->taslar, gidilecekYer)) {
      // Sah kurallarına uygunsa hareket edilir :
      if(this->taslar[tasSira]->getTakim() == beyaz){
        // Şah hareket ettiği için ileride rok yapamaz:
        beyazRok = make_pair(false, false);
      }else if(this->taslar[tasSira]->getTakim() == siyah){
        siyahRok = make_pair(false, false);
      }
      return this->tasHareket(gidilecekYer,rakipTasSira,rakiptasVarMi,tasSira);
  }
}

return false;
}

// Rakip takımın sahının konumunu döndürür :
pair<int, int> Tahta::rakipTakimSahKonum(takim hareketEdenTakimKim){

  for (int i  = 0; i < taslar.size(); i++) {
    if(taslar[i]->getTakim() == hareketEdenTakimKim){
      continue;
    }

    if(taslar[i]->getAdi() == "Sah"){
      return taslar[i]->getKonum();
    }
  }
  return make_pair(0, 0);
}

// Rakip takımının Sahının sırasını gönderir :
int Tahta::rakipTakimSahSira(takim hareketEdenTakimKim)
{
  pair<int, int> takimSahKonum;

  for (int i  = 0; i < taslar.size(); i++) {
    if(taslar[i]->getTakim() == hareketEdenTakimKim){
      continue;
    }

    if(taslar[i]->getAdi() == "Sah"){
      return i;
    }
  }
  return 0;
}

// Gidilecek yere ulaşan tas var mı diye bakılır :
pair<bool, int> Tahta::tehditVarMi(pair<int, int> gidilecekYer, takim hareketEdenTakimKim){
  for(int i = 0; i < taslar.size(); i++){

    if(taslar[i]->getTakim() != hareketEdenTakimKim){
      continue;
    }

    if(this->taslar[i]->getAdi() == "Piyon"){
      if (((Piyon*)this->taslar[i])->yolKntrl(taslar, gidilecekYer, *this)) {
          return make_pair(true, i);
      }
    }else if(taslar[i]->getAdi() == "Kale"){
      if (((Kale*)this->taslar[i])->yolKntrl(taslar, gidilecekYer)) {
          return make_pair(true, i);
      }
    }else if(taslar[i]->getAdi() == "At"){
      if (((At*)this->taslar[i])->yolKntrl(taslar, gidilecekYer)) {
          return make_pair(true, i);
      }
    }else if(taslar[i]->getAdi() == "Fil"){
      if (((Fil*)this->taslar[i])->yolKntrl(taslar, gidilecekYer)) {
          return make_pair(true, i);
      }
    }else if(taslar[i]->getAdi() == "Vezir"){
      if (((Vezir*)this->taslar[i])->yolKntrl(taslar, gidilecekYer)) {
        return make_pair(true, i);
      }
    }
  }

  return make_pair(false, 0);

}

// Saha ulaşabilecek tas var mı diye bakılır :
bool Tahta::sahVarMi(takim hareketEdenTakim){

  return (tehditVarMi(rakipTakimSahKonum(hareketEdenTakim),hareketEdenTakim)).first;

  }

// Mat mı kontrol edilir :
bool Tahta::sahMatMi(takim hareketEdenTakim, int tehditSira){

  // Şah kurtarılabilir mi ? :
  // Çevrede taş yoksa ve oraya gidince şah olmuyorsa return false :

  string strSahTakim;

  if(hareketEdenTakim == beyaz){
    strSahTakim = "Siyah";
  }else{
    strSahTakim = "Beyaz";
  }
  pair <int, int> sahKonum = rakipTakimSahKonum(hareketEdenTakim);
  pair <int, int> tehditKonum = taslar[tehditSira]->getKonum();

  vector<Tas*> taslarKopya;

  // Taslar Silinir :
  for (int i = 0; i < taslarKopya.size(); i++)
  {
    delete(taslarKopya[i]);
  }
  taslarKopya.clear();

  // Taşlar kopyalanır:
  for (int i = 0; i < getTaslar()->size(); i++) {
    taslarKopya.push_back(new Tas(*(*(getTaslar()))[i]));
  }
  int sahSira = rakipTakimSahSira(hareketEdenTakim);

  // Rok Yaparak Kaçabillir Mi? :
  if((rokYapma(strSahTakim, "kısa rok") == true && sahVarMi(hareketEdenTakim) == false) || (rokYapma(strSahTakim, "uzun rok") == true && sahVarMi(hareketEdenTakim) == false)){
    setTaslar(taslarKopya);
    return false;
  }

  for (int i = 0; i < taslarKopya.size(); i++)
  {
    delete(taslarKopya[i]);
  }
  taslarKopya.clear();

  for(int x = (sahKonum.first-1); x <= (sahKonum.first+1); x++){

    for(int y = (sahKonum.second-1); y <= (sahKonum.second+1); y++){

      if(((Sah*)this->taslar[sahSira])->yolKntrl(this->taslar, make_pair(x,y))){

        for (int i = 0; i < taslarKopya.size(); i++)
        {
          delete(taslarKopya[i]);
        }
        taslarKopya.clear();
        // Taşlar kopyalanır:
        for (int i = 0; i < getTaslar()->size(); i++) {
          taslarKopya.push_back(new Tas(*(*(getTaslar()))[i]));
        }
        if(hareketEt(strSahTakim, sahKonum, make_pair(x,y)) && sahVarMi(hareketEdenTakim) == false){
          setTaslar(taslarKopya);
          return false;
        }

        setTaslar(taslarKopya);
      }
    }
  }

  vector< pair<int, int> > aralarKonum;
// TODO : aralarKonum = Tehdit ile Şah arasındaki konumlar.

  // Eğer şah çeken at değilse :
  if (taslar[tehditSira]->getAdi() != "At") {
    // Araya taş girebilir mi ? :
    if(tehditKonum.first == sahKonum.first){
      // X olarak aynı hizadalar :
      if(tehditKonum.second > sahKonum.second){
        // Tehdit sağ tarafta:
        for (int i = sahKonum.second+1; i < tehditKonum.second; i++) {
          aralarKonum.push_back(make_pair(sahKonum.first, i));
        }
      }else{
        // Tehdit sol tarafta:
        for (int i = tehditKonum.second+1; i < sahKonum.second; i++) {
          aralarKonum.push_back(make_pair(sahKonum.first, i));
        }
      }
    }else if(tehditKonum.second == sahKonum.second){
      // Y olarak aynı hizadalar :
      if(tehditKonum.first > sahKonum.first){
        // Tehdit aşağı tarafta:
        for (int i = sahKonum.first+1; i < tehditKonum.first; i++) {
          aralarKonum.push_back(make_pair(i, sahKonum.second));
        }
      }else{
        // Tehdit yukari tarafta:
        for (int i = tehditKonum.first+1; i < sahKonum.first; i++) {
          aralarKonum.push_back(make_pair(i, sahKonum.second));
        }
      }
    }else{
      // Çaprazlardan saldırılmış :
      if(tehditKonum.second < sahKonum.second){
        // Tehdit solda:
        if(tehditKonum.first < sahKonum.first){
          // Sol Yukarıda
          for (int x = tehditKonum.first+1, y = tehditKonum.second+1; x < sahKonum.first; x++, y++) {
            aralarKonum.push_back(make_pair(x, y));
          }
        }else if(tehditKonum.first > sahKonum.first){
          // Sol aşağıda
          for (int x = sahKonum.first+1, y = sahKonum.second-1; x < tehditKonum.first; x++, y--) {
            aralarKonum.push_back(make_pair(x, y));
          }
        }
      }else if(tehditKonum.second > sahKonum.second){
        // Tehdit sağ da
        if(tehditKonum.first < sahKonum.first){
          // Sağ yukarıda
          for (int x = tehditKonum.first+1, y = tehditKonum.second-1; x < sahKonum.first; x++, y--) {
            aralarKonum.push_back(make_pair(x, y));
          }
        }else if(tehditKonum.first > sahKonum.first){
          // Sağ aşağıda
          for (int x = sahKonum.first+1, y = sahKonum.second+1; x < tehditKonum.first; x++, y++) {
            aralarKonum.push_back(make_pair(x, y));
          }
        }
      }
    }
  }

  takim tmpTakim;
  if (hareketEdenTakim == beyaz)
  {
    tmpTakim = siyah;
  }
  else{
    tmpTakim = beyaz;
  }
  // Araya girebilen var mı ? :
  for (int i = 0; i < aralarKonum.size(); i++) {
    if(tehditVarMi(aralarKonum[i], tmpTakim).first){
      return false;
    }
  }

  // Şah çeken taşı yiyebilen taş var mı ? :
    if(tehditVarMi(tehditKonum, tmpTakim).first){
      return false;
    }

  // aralarKonum temizleme :
  aralarKonum.clear();

  // Taşlar Kopya temizleme :
  for (int i = 0; i < taslarKopya.size(); i++)
  {
    delete(taslarKopya[i]);
  }
  taslarKopya.clear();

  // Hiçbirine takılmadıysa Şah Mat olur.
  return true;
}

bool Tahta::rokYapma(string oyunSirasi, string hangiRok){

  // Taşlar oynanmış mı ? :
  if (karsilastir(hangiRok, KISA_ROK, 8) == true) {
    // Kısa Rok:
    if(oyunSirasi == "Beyaz"){
      // Beyaz :
      if(beyazRok.first == false){
        return false;
      }

      for(int x = 0, y = 5; y < 7; y++){
        for (int i = 0; i < taslar.size(); i++) {
          if(taslar[i]->getKonum() == make_pair(x, y)){
            return false;
          }
        }
      }

      for (int i = 0; i < taslar.size(); i++) {
        if(taslar[i]->getKonum() == make_pair(0, 7)){
          taslar[i]->setKonum(make_pair(0, 5));
        }else if(taslar[i]->getKonum() == make_pair(0, 4)){
          taslar[i]->setKonum(make_pair(0, 6));
        }else{
          continue;
        }
      }

    }else{
      // Siyah :
      if(siyahRok.first == false){
        return false;
      }

      for(int x = 7, y = 5; y < 7; y++){
        for (int i = 0; i < taslar.size(); i++) {
          if(taslar[i]->getKonum() == make_pair(x, y)){
            return false;
          }
        }
      }

      for (int i = 0; i < taslar.size(); i++) {
        if(taslar[i]->getKonum() == make_pair(7, 7)){
          taslar[i]->setKonum(make_pair(7, 5));
        }else if(taslar[i]->getKonum() == make_pair(7, 4)){
          taslar[i]->setKonum(make_pair(7, 6));
        }else{
          continue;
        }
      }

    }
  }else{
    // Uzun Rok:
    if(oyunSirasi == "Beyaz"){
      // Beyaz :
      if(beyazRok.second == false){
        return false;
      }

      for(int x = 0, y = 1; y < 4; y++){
        for (int i = 0; i < taslar.size(); i++) {
          if(taslar[i]->getKonum() == make_pair(x, y)){
            return false;
          }
        }
      }

      for (int i = 0; i < taslar.size(); i++) {
        if(taslar[i]->getKonum() == make_pair(0, 0)){
          taslar[i]->setKonum(make_pair(0, 3));
        }else if(taslar[i]->getKonum() == make_pair(0, 4)){
          taslar[i]->setKonum(make_pair(0, 2));
        }else{
          continue;
        }
      }

    }else{
      // Siyah :
      if(siyahRok.second == false){
        return false;
      }

      for(int x = 7, y = 1; y < 4; y++){
        for (int i = 0; i < taslar.size(); i++) {
          if(taslar[i]->getKonum() == make_pair(x, y)){
            return false;
          }
        }
      }

      for (int i = 0; i < taslar.size(); i++) {
        if(taslar[i]->getKonum() == make_pair(7, 0)){
          taslar[i]->setKonum(make_pair(7, 3));
        }else if(taslar[i]->getKonum() == make_pair(7, 4)){
          taslar[i]->setKonum(make_pair(7, 2));
        }else{
          continue;
        }
      }

    }
  }

  return true;
}

// Gelen iki string'i karşılaştırır :
bool Tahta::karsilastir(string str1, string str2, int karakterSayisi){

  for (int i = 0; i < karakterSayisi; i++) {
    if(str1[i] != str2[i]){
      return false;
    }
  }

  return true;
}

// Pat mı diye bakar :
bool Tahta::patMi(takim oyunSirasi){

  string strOyunSirasi;

  if(oyunSirasi == beyaz){
    oyunSirasi = siyah;
    strOyunSirasi = "Siyah";
  }else{
    oyunSirasi = beyaz;
    strOyunSirasi = "Beyaz";
  }

  vector<Tas*> taslarKopya;

  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {

    if(tehditVarMi(make_pair(x, y), oyunSirasi).first){

      // Taşlar kopyalanır:
      for (int i = 0; i < getTaslar()->size(); i++) {
        taslarKopya.push_back(new Tas(*(*(getTaslar()))[i]));
      }

      if(hareketEt(strOyunSirasi, taslar[(tehditVarMi(make_pair(x, y), oyunSirasi).second)]->getKonum(), make_pair(x, y)) && !(sahVarMi(oyunSirasi))){
        setTaslar(taslarKopya);
        return false;
      }else{
        setTaslar(taslarKopya);
      }

      for (int i = 0; i < taslarKopya.size(); i++)
      {
        delete(taslarKopya[i]);
      }
      taslarKopya.clear();

    }
   }
  }

  cout << "Pat !" << endl;

  if (getOsAdi() == "Mac") {
    // Mac icin seslendirme :
    system("say Pat!");
  }

  return true;
}

// Sayacın değerini döndürür :
int Tahta::getGeriSayim(){
  return this->geriSayim;
}

// Sayacı ayarlar :
void Tahta::setGeriSayim(int sayac){
  this->geriSayim = sayac;
}

// gecerkenAlma değişkenini döndürür :
pair<pair<int, int>, takim> Tahta::getGecerkenAlma(){
  return this->gecerkenAlma;
}

// gecerkenAlma değişkenini ayarlar :
void Tahta::setGecerkenAlma(pair<int, int> gectigiYer, takim renk){
  this->gecerkenAlma = make_pair( gectigiYer, renk );
}

// OS Adını döner :
string Tahta::getOsAdi(){
  #ifdef _WIN32
  return "Windows";
  #elif _WIN64
  return "Windows";
  #elif __APPLE__ || __MACH__
  return "Mac";
  #elif __linux__
  return "Linux";
  #else
  return "Other";
  #endif
}
