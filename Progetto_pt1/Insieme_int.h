#ifndef INSIEME_INT_H
#define INSIEME_INT_H

#include<iostream>
using namespace std;

class Insieme_int {
 public:
  friend class Relazione;
  friend ostream& operator<<(ostream&, const Insieme_int&);
  bool add(int);
  bool remove(int);
  bool see(int) const;
  int size() const;
  bool operator==(const Insieme_int&);
  bool operator!=(const Insieme_int&);
  Insieme_int operator+(const Insieme_int&); 
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
    nodo(int&, const smartp&);
    int num;
    smartp next;
    int reference;
  };   //end class nodo
  smartp first;
};  // end class insieme_int

#endif
