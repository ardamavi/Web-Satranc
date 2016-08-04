// Arda Mavi - ardamavi.com

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "Tas.h"

using namespace std;

  // Taşın görsel halini döner (Unicode) :
  string Tas::tasKisaltmasi(){

  string kisaltma = " ";

    // Unicode :
    switch (adi[0]) {
      case 'P':
      kisaltma += "\u265F";
      break;
      case 'K':
      kisaltma += "\u265C";
      break;
      case 'A':
      kisaltma += "\u265E";
      break;
      case 'F':
      kisaltma += "\u265D";
      break;
      case 'V':
      kisaltma += "\u265B";
      break;
      case 'S':
      kisaltma += "\u265A";
      break;
    }

  kisaltma += " ";

  return kisaltma;
}


Tas::Tas(takim renk, string adi, int x, int y){
    this->renk = renk;
    this->adi = adi;
    this->konum = make_pair(x, y);
}

Tas::Tas(Tas &tas)
{
  Tas tmp(tas.renk, tas.adi, tas.konum.first, tas.konum.second);
  this->renk = tmp.renk;
  this->adi = tmp.adi;
  this->konum = tmp.konum;
}

/*Tas::~Tas()
{
  delete this->konum;
  delete this->renk;
  delete this->adi;
}*/

pair<int, int> Tas::getKonum() {
    return this->konum;
}

takim  Tas::getTakim(){
    return this->renk;
}

string Tas::getAdi(){
    return this->adi;
}

void Tas::setKonum(pair <int, int> gidilecekYer){
    this->konum = gidilecekYer;
}
