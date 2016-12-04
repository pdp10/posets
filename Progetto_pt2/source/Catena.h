#ifndef CATENA_H
#define CATENA_H

#include "Relazione.h"
#include "Poset.h"
#include"Insieme.h"
#include "Coppia.h"
#include<iostream>
#include<string>
using namespace std;


class Catena: public Poset {
 private:
  static string nome;
 public:
  friend ostream& operator<<(ostream&, const Catena&);
  Catena();
  Catena(Relazione);
  Catena(Poset);  //Dal gcc 3.3.3 da' problemi!
  Catena(const int&);
  char top() const;
  char bottom() const;
  virtual Insieme<char> massimali() const;
  virtual Insieme<char> minimali() const;
  virtual Insieme<char> massimali(const Insieme<char>&) const;
  virtual Insieme<char> minimali(const Insieme<char>&) const;
  virtual int livello() const;    
  //virtual Insieme<char> livello(const int&) const;    //e' uguale a Poset                      
  virtual string get_nome() const;
  virtual ~Catena();
};

#endif
