#ifndef INSIEME_COPPIA_H
#define INSIEME_COPPIA_H

#include"Coppia.h"
#include<iostream>
using namespace std;

class Insieme_Coppia {
 public:
  friend class Relazione;
  friend ostream& operator<<(ostream&, const Insieme_Coppia&);
  bool add(const Coppia&);
  bool remove(const Coppia&);
  bool see(const Coppia&) const;
  int size() const;
  bool operator==(const Insieme_Coppia&);
  bool operator!=(const Insieme_Coppia&);
  Insieme_Coppia operator+(const Insieme_Coppia&); 
 private:
  class nodo;
  class smartp {
   public:
    nodo* point;
    smartp(nodo* =0);
    smartp(const smartp&);
    ~smartp();
    smartp& operator=(const smartp&);
    nodo& operator*() const;
    nodo* operator->() const;
    bool operator==(smartp) const;
    bool operator!=(smartp) const;
  };  //end class smartp
  class nodo {
   public:
    nodo();
    nodo(Coppia&, const smartp&);
    Coppia cp;
    smartp next;
    int reference;
  };   //end class nodo
  smartp first;
};  // end class Insieme_Coppia

#endif
