// Arda Mavi - ardamavi.com

#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include "Color.h" // namespace Color
#include "Tahta.h"
#include "Tas.h"
#include "Piyon.h"
#include "At.h"
#include "Fil.h"
#include "Sah.h"
#include "Kale.h"
#include "Vezir.h"
#include "Color.h"

Color::Modifier defaultColorfg(Color::FG_DEFAULT);
Color::Modifier defaultColorbg(Color::BG_DEFAULT);

using namespace std;

int harfToSayi(char harf){
  return ((int)(harf)-97);
}

int sayiCharToSayi(char sayiChar){
  return ((int)sayiChar-49);
}

int main(){

    // Bir tahta oluşturulur :
    Tahta tahta;

    if (tahta.getOsAdi() == "Mac" || tahta.getOsAdi() == "Linux") {
      // Mac icin ekran temizleme :
      system("clear");
    }else if(tahta.getOsAdi() == "Windows"){
      // Windows için silme :
      system("cls");
    }

    // Ekrandaki renkleri ayarlama :
    cout << defaultColorbg << defaultColorfg;

    // Oyun başlangıcı bilgilendirme yazıları :
    cout << "- Satranç -\nArda Mavi - ardamavi.com" << endl;
    cout << "Girişler SayiHarf seklinde olmalidir. Orn: 2e" << endl;
    cout << "Rok girişleri için: \"uzun rok\" ya da \"kısa rok\" diye yazmalısınız." << endl;
    cout << "Oyundan çıkmak için klavyeden \"kntrl-c\" tuslarına basınız ya da \"cikis\" yazınız.\n" << endl;

    string kazanan = "Yok";
    string oyunSirasi = "Siyah";
    pair <int, int> tasinKonumu;
    pair <int, int> oynanacakYer;
    bool sahDurum = false;

    // İleride vektör boyutunu tutacak olan değişken :
    int eskiTaslarSize;

  do{

    // Siradaki Oyuncu Dondurulur.
    if(oyunSirasi == "Beyaz"){
        oyunSirasi = "Siyah";
    }else{
        oyunSirasi = "Beyaz";
    }

    // Turun doğru olup olmadığını kontrol eder :
    bool oynamaTamamMi = true;

    takim takimOyunSirasi;
    takim takimEskiOyunSirasi;

    do{

      // Ekrandaki renkleri orijinaline ayarlama :
      cout << defaultColorbg << defaultColorfg << endl;

      // Tahta cizilir:
      tahta.tahtaCiz();

      // Ekrandaki renkleri orijinaline ayarlama :
      cout << defaultColorbg << defaultColorfg << endl;

      // Turun doğru oynanıp oynanmadığına göre ekrana çıktı verir :
      // Not : oynamaTamamMi değişkeni tur sonunda ayarlanır.
      if(!oynamaTamamMi){
        cout << "\nHatalı Giriş !\n";
        if (tahta.getOsAdi() == "Mac") {
          // Mac icin seslendirme :
          system("say Hatalı giriş!");
        }
      }

    // Mac icin oyun sırası seslendirme:
    cout << "\nOyun Sırası: " << oyunSirasi << endl;
    if(oyunSirasi == "Beyaz"){
      if (tahta.getOsAdi() == "Mac") {
        // Mac icin seslendirme :
        system("say Oyun sırası beyaz takımda!");
      }
    }else if(oyunSirasi == "Siyah"){
      if (tahta.getOsAdi() == "Mac") {
        // Mac icin seslendirme :
        system("say Oyun sırası siyah takımda!");
      }
    }

    // Eski oyun sırasını tutan değişken :
    string eskiOyunSirasi;

    if(oyunSirasi == "Beyaz"){
      takimOyunSirasi = beyaz;
      eskiOyunSirasi = "Siyah";
      takimEskiOyunSirasi = siyah;
    }else if(oyunSirasi == "Siyah"){
      takimOyunSirasi = siyah;
      eskiOyunSirasi = "Beyaz";
      takimEskiOyunSirasi = beyaz;
    }

    // Yanlış oynama durumunda tasların yerini geri almak için :
    vector<Tas*> taslarKopya;

    tahta.beyazRokKopya = tahta.beyazRok;
    tahta.siyahRokKopya = tahta.siyahRok;

    // Taşlar kopyalanır:
    for (int i = 0; i < tahta.getTaslar()->size(); i++) {
      taslarKopya.push_back(new Tas(*(*(tahta.getTaslar()))[i]));
    }

    // Tahtadaki tasların sayısı atanır :
    eskiTaslarSize = tahta.getTaslar()->size();

    // Oynanacak taşın konumu alınır :
    string tasinKonumuChar;
    cout << "\nTaşın konumunu giriniz: ";
    getline(cin, tasinKonumuChar);

    if(tasinKonumuChar == "cikis"){

      if (tahta.getOsAdi() == "Mac" || tahta.getOsAdi() == "Linux") {
        // Mac icin ekran temizleme :
        system("clear");
      }else if(tahta.getOsAdi() == "Windows"){
        // Windows için silme :
        system("cls");
      }

      cout << "Oyundan Çıkıldı !" << endl;
      kazanan = "Berabere";
      break;
    }

    // Oyunda rok yapma durumunu kontrol eder :
    if(tahta.karsilastir(tasinKonumuChar, KISA_ROK, 8) != true && tahta.karsilastir(tasinKonumuChar, UZUN_ROK, 8) != true){
      // Eğer rok yapılmak istenmiyorsa :

      if(!(((0 <= sayiCharToSayi(tasinKonumuChar[0])) && (sayiCharToSayi(tasinKonumuChar[0])) < 8) && ((0 <= harfToSayi(tasinKonumuChar[1])) && (harfToSayi(tasinKonumuChar[1]) < 8)))){
        oynamaTamamMi = false;
        if (tahta.getOsAdi() == "Mac" || tahta.getOsAdi() == "Linux") {
          // Mac icin ekran temizleme :
          system("clear");
        }else if(tahta.getOsAdi() == "Windows"){
          // Windows için silme :
          system("cls");
        }
        continue;
      }

      // Tasın konumu pair olarak tutulur :
      tasinKonumu.first = sayiCharToSayi(tasinKonumuChar[0]);
      tasinKonumu.second = harfToSayi(tasinKonumuChar[1]);

      // Taşın oynamak istenilen yeri alınır :
      string oynanacakYerChar;
      cout << "\nTaşı oynayacağınız konumu giriniz: ";
      getline(cin, oynanacakYerChar);

      if(!(((0 <= sayiCharToSayi(oynanacakYerChar[0])) && (sayiCharToSayi(oynanacakYerChar[0])) < 8) && ((0 <= harfToSayi(oynanacakYerChar[1])) && (harfToSayi(oynanacakYerChar[1]) < 8)))){
        oynamaTamamMi = false;
        if (tahta.getOsAdi() == "Mac" || tahta.getOsAdi() == "Linux") {
          // Mac icin ekran temizleme :
          system("clear");
        }else if(tahta.getOsAdi() == "Windows"){
          // Windows için silme :
          system("cls");
        }
        continue;
      }

      // oynanacak yerin konumu pair olarak tutulur :
      oynanacakYer.first = sayiCharToSayi(oynanacakYerChar[0]);
      oynanacakYer.second = harfToSayi(oynanacakYerChar[1]);
    }

    // Eğer şah çekildiyse :
    // Not : sahDurum turun sonunda ayarlanır.
    if(sahDurum == true){

      if(tahta.karsilastir(tasinKonumuChar, KISA_ROK, 8) != true && tahta.karsilastir(tasinKonumuChar, UZUN_ROK, 8) != true){
        // Eğer rok yapılmak istenmiyorsa tas oynanır :
        tahta.hareketEt(oyunSirasi, tasinKonumu, oynanacakYer);
      }else{
        // Rok yapılır :
        tahta.rokYapma(oyunSirasi, tasinKonumuChar);
      }

      // sahDurum güncellenir :
      sahDurum = tahta.sahVarMi(takimEskiOyunSirasi);

      // Hala Şah durumu varsa :
      if(sahDurum == true){
        // Kopyalanan taslar tahtaya dizilir atanir :
        tahta.setTaslar(taslarKopya);

        tahta.beyazRok = tahta.beyazRokKopya;
        tahta.siyahRok = tahta.siyahRokKopya;

        // cout << "Şahınızı kurtarmanız lazım !" << endl;

        if (tahta.getOsAdi() == "Mac") {
          // Mac icin seslendirme :
          system("say Şahınızı kurtarmanız lazım!");
        }

        // Sah durumundan kurtulmadığı için tur tekrar oynanacaktır :
        oynamaTamamMi = false;
      }else{
        //Dogru oynanmis ise yeni tur için onay verilir :
        oynamaTamamMi = true;
      }

    }else{

      if(tahta.karsilastir(tasinKonumuChar, "kısa rok", 8) != true && tahta.karsilastir(tasinKonumuChar, UZUN_ROK, 8) != true){
        // Eğer rok yapılmak istenmiyorsa :

        // Hareketin doğru olup olmadığı alınır :
        oynamaTamamMi = (tahta.hareketEt(oyunSirasi, tasinKonumu,oynanacakYer));
      }else{
        // // Hareketin doğru olup olmadığı alınır :
        oynamaTamamMi = tahta.rokYapma(oyunSirasi, tasinKonumuChar);
      }

      // Oyun sonrasında sah durumu var mı bakılır :
      if(tahta.sahVarMi(takimEskiOyunSirasi)){
        // Sah durumu varsa :

        // Tur tekrarlama için ayar yapılır :
        oynamaTamamMi = false;

        // Uyarı verilir :
        // cout << "Şahınızı tehlikeye atamazsınız !" << endl;

        // Hareket önceki tasların konumu tahtaya yerleştirilir :
        tahta.setTaslar(taslarKopya);

        tahta.beyazRok = tahta.beyazRokKopya;
        tahta.siyahRok = tahta.siyahRokKopya;

        if (tahta.getOsAdi() == "Mac") {
          // Mac icin seslendirme :
          system("say Şahınızı tehlikeye atamazsınız!");
        }
      }
    }

    if (tahta.getOsAdi() == "Mac" || tahta.getOsAdi() == "Linux") {
      // Mac icin ekran temizleme :
      system("clear");
    }else if(tahta.getOsAdi() == "Windows"){
      // Windows için silme :
      system("cls");
    }

    // Taslar kopya silinir :
    // Taslar kopya pointer olduğu için ilk içi temizelenir
    // sonra pointerlar silinir
    for (int i = 0; i < taslarKopya.size(); i++)
    {
      delete(taslarKopya[i]);
    }
    taslarKopya.clear();

    // Eğer oynamaTamam değilse tur tekrarlanır.
  }while(!oynamaTamamMi);

    // Şah var mı diye bakılır ve ileride kullanmak için saklanır :
    sahDurum = tahta.sahVarMi(takimOyunSirasi);

    // Sah ise sah olduğu belirtilir :
    if(sahDurum){
      //cout << "Şah !" << endl;

      if (tahta.getOsAdi() == "Mac") {
        // Mac icin seslendirme :
        system("say Şah!");
      }

      // Oyunun mat olup olmadığı belirlenir:
      if(tahta.sahMatMi(takimOyunSirasi, tahta.tehditVarMi(tahta.rakipTakimSahKonum(takimOyunSirasi), takimOyunSirasi).second)){
        // Mat oldu !
        //cout << "Mat !" << endl;
        if (tahta.getOsAdi() == "Mac") {
          // Mac icin seslendirme :
          system("say Mat!");
        }

        // Kazanan mat edendir :
        kazanan = oyunSirasi;
      }

    }

    // Eğer pat olursa oyun berabere biter :
    if(kazanan == "Yok" && tahta.patMi(takimOyunSirasi)){
      kazanan = "Berabere";
    }

    // 50 adım kuralı kontrol edilir :
    if(tahta.getGeriSayim() <= 0){
      cout << "50 adım kuralından dolayı oyun berabere bitmiştir !" << endl;
      kazanan = "Berabere";
    }

    // Tur sonunda 50 adım kuralı için sayaç bir azaltılır :
    tahta.setGeriSayim(tahta.getGeriSayim()-1);

    string oynayanTas;

    // Taslar gezilir :
    for (int i = 0; i < tahta.getTaslar()->size(); i++) {
      // Tas oynanacak yerde ise :
      if((*(tahta.getTaslar()))[i]->getKonum() == oynanacakYer){
        // Oynayan tasın adı tutulur :
        oynayanTas = (*(tahta.getTaslar()))[i]->getAdi();
      }
    }

    // Not : Bu kısım 50 adım kuralı ile ilgilirdir :
    // Eğer oynayan piyon ise ya da bir taş yenmişse :
    if((tahta.getTaslar()->size() != eskiTaslarSize) || oynayanTas == "Piyon"){
      // Geri sayım yeniden başlatılır :
      tahta.setGeriSayim(50);
    }

    // En passant kuralı için:
    // Oynayan taş piyon ise ve En Passant kuralı kapalı değilse :
    if((tahta.getGecerkenAlma().second != yok) && (oynayanTas == "Piyon")){
      // Oynanacak yer Piyonun arkada bıraktığı yer ise :
        if(oynanacakYer == tahta.getGecerkenAlma().first){
          // Taslar gezilir :
          for (int i = 0; i < tahta.getTaslar()->size(); i++) {
            // Taş atlayan taş ise :
            if((*(tahta.getTaslar()))[i]->getKonum() == make_pair((oynanacakYer.first - takimOyunSirasi), (oynanacakYer.second))){

              // Atlayan tas yenir(taslar vektöründen silinir) :
              tahta.getTaslar()->erase((*(tahta.getTaslar())).begin() + i);
            }
          }
        }
    }
    // En passant aktif değil ise :
    if(((tahta.getGecerkenAlma().second == yok) && (oynayanTas == "Piyon") && (tasinKonumu.second == oynanacakYer.second) && ((oynanacakYer.first - tasinKonumu.first)%2 ==  0))){
      // En passant aktif ise kural için ayarlar yapılır :
      tahta.setGecerkenAlma(make_pair((oynanacakYer.first - takimOyunSirasi), (oynanacakYer.second)), takimOyunSirasi );
    }else if(tahta.getGecerkenAlma().second == takimEskiOyunSirasi){
      // En passant aktif değil ise ve kimse geçilen yere girmeye çalışmadıysa :
      tahta.setGecerkenAlma(make_pair((oynanacakYer.first - takimOyunSirasi), (oynanacakYer.second)), yok );
    }

    // Bir kazanan olana kadat oyun sürer :
  }while(kazanan == "Yok");

  // Son kez tahta cizilir:
  tahta.tahtaCiz();

  // Terminal orijinal rengine ayarlanır :
  cout << defaultColorbg << defaultColorfg;

  cout << "\nOyun Bitti\n" << "\nKazanan: " << kazanan << endl;

  if (tahta.getOsAdi() == "Mac") {
    // Mac icin seslendirme :
    system("say Oyun Bitti!");
  }

  // Mac icin kazanan seslendirme:
  if(kazanan == "Beyaz"){
    system("say Kazanan Beyaz takım!");
  }else if(kazanan == "Siyah"){
    system("say Kazanan Siyah takım!");
  }else if(kazanan == "Berabere"){
    system("say Kazanan yok! Berabere!");
  }else{
    system("say Kazanan yok!");
  }

    cout << "Son" << endl;

    return 0;
}
