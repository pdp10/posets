#ifndef POSET_H                           //Poset p=(P,<=)
#define POSET_H                   //poset e' una relazione particolare

#include"Relazione.h"
#include"Insieme.h"
#include<string>
#include<iostream>
using namespace std;

class Poset: public Relazione {
 private:
  static string nome;
 public:
  friend ostream& operator<<(ostream&, const Poset&);
  Poset();
  Poset(Relazione);
  virtual bool add(const char&, const char&);
  virtual Insieme<char> massimali(const Insieme<char>&) const;     
  virtual Insieme<char> minimali(const Insieme<char>&) const;
  virtual Insieme<char> massimali() const;                         
  virtual Insieme<char> minimali() const;
  bool catena() const;    
  Relazione copertura() const;
  virtual int livello() const;                           
  virtual Insieme<char> livello(const int&) const;
  virtual string get_nome() const;
  virtual ~Poset();
};

#endif
