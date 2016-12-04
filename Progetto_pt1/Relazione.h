
#ifndef RELAZIONE_H
#define RELAZIONE_H

#include"Insieme_int.h"
#include"Insieme_Coppia.h"
#include<iostream>
using namespace std;

class Relazione{
 public:
  friend ostream& operator<<(ostream&, const Relazione&);
  Relazione();
  Relazione(const Insieme_int&, const Insieme_Coppia&); 
  bool add(int, int);
  bool remove(int,int);
  Relazione operator*(const Relazione&);
  Relazione inversa();
  bool operator()(int,int);
  Insieme_int post(int);
  bool total();
  void trans_closure();
  void reflex_closure();
 private:
  Insieme_int I;
  Insieme_Coppia R;
};

#endif
