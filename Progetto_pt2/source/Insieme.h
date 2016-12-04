#ifndef INSIEME_H
#define INSIEME_H

#include <string>
#include "Coppia.h"
#include <iostream>
using namespace std;

template<class T>
class Insieme {
 public:
  friend class Relazione;
  friend class Poset;
  friend class Catena;
  friend ostream& operator<< <T>(ostream&, const Insieme<T>&);
  bool add(T);
  bool remove(T);
  bool see(T) const;
  bool empty() const;
  int size() const;
  bool operator==(const Insieme&);
  bool operator!=(const Insieme&);
  Insieme operator+(const Insieme&);
  Insieme operator-(const Insieme&); 
  bool sottoinsieme(const Insieme&) const;
  const char* write() const;    //per la stampa nella pt grafica
  const char* write_I() const;
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
    nodo(T&, const smartp&);
    T info;
    smartp next;
    int reference;
  };   //end class nodo
  smartp first;
};  // end class Insieme




//CLASS SMARTP
template<class T>
Insieme<T>::smartp::smartp(nodo* _point): point(_point) { if(point) point->reference++; }

template<class T>
Insieme<T>::smartp::smartp(const smartp& _sp): point(_sp.point) { if(point) point->reference++; }

template<class T>
Insieme<T>::smartp::~smartp() {
  if(point) {
    point->reference--;
    if(point->reference == 0)
      delete point;
  }
}

template<class T>
typename Insieme<T>::smartp& Insieme<T>::smartp::operator=(const smartp& _sp) {  //typename per togliere i warning
  if(this != &_sp) {                                                             //typename esplicito
    nodo* temp = point;
    point = _sp.point;
    if(point) point->reference++;
    if(temp) {
      temp->reference--;
      if(temp->reference == 0) delete temp;
    }
  }
  return *this;
}

template<class T>
typename Insieme<T>::nodo& Insieme<T>::smartp::operator*() const { return *point; }

template<class T>
typename Insieme<T>::nodo* Insieme<T>::smartp::operator->() const { return point; }

template<class T>
bool Insieme<T>::smartp::operator==(smartp _sp) const { return point == _sp.point; }

template<class T>
bool Insieme<T>::smartp::operator!=(smartp _sp) const { return point != _sp.point; }
  


//CLASS NODO
template<class T>
Insieme<T>::nodo::nodo(): next(0), reference(0) {}

template<class T>
Insieme<T>::nodo::nodo(T& _info, const smartp& _sp): info(_info), next(_sp), reference(0) {}



//FUNZIONI AUSILIARIE

template<class T>
int Insieme<T>::size() const { 
   int count = 0;
   smartp p = first;
   while(p != 0) {
     count++;
     p = p->next;
   }
   return count;
}

template<class T>
bool Insieme<T>::empty() const {   return first == 0; }

template<class T>
bool Insieme<T>::see(T x) const {               // scorre l'insieme e ritorna true se x e' presente, false altrimenti
   smartp p = first;
   bool t = false;
   while(p != 0 && !t) {
      if(p->info == x)  t = true;
      p = p->next;
   }
   return t;
} 



//CLASS INSIEME
template<class T>
ostream& operator<<(ostream& os, const Insieme<T>& i) {
  if(i.empty()) return os << "Insieme vuoto"; 
  else {
    typename Insieme<T>::smartp sp = i.first;    
    os <<'{'<< sp->info;
    while(sp->next != 0) {
      os <<',' << sp->next->info;
      sp = sp->next;
    }
  os << '}';
  }
  return os;
}

template<class T>
bool Insieme<T>::add(T _info) {
  if(see(_info))  return false;              // _info e' presente
  if(first == 0){                          //insieme vuoto
     nodo* p = new nodo;
     p->next = first;
     first = p;
     p->info = _info;
  }
  else {                              // in coda
    smartp s = first;
    bool ins = false;
    while(s != 0 && !ins){
      if(s->next == 0) {
        nodo* q = new nodo;
	q->next = 0;
	q->info = _info;
	s->next = q;
	ins = true;            // uscita dal ciclo 
      }
      s = s->next;
      }
    }
  return true;
}


template<class T>
bool Insieme<T>::remove(T _info) {
  bool t = false;
  smartp p = first;
  if(p != 0 && p->next == 0){              // caso 1 elem
    if(p->info == _info) 
       { first = 0; return true; }
    else  return t;
  }
  if(p != 0 && p->next != 0) {     //caso piu' di 1 elemento 
    smartp pred = p;
    p = p->next;
    if(pred->info == _info)
        { first = p; return true; }
    else 
       while(p != 0 && !t)  {
          if(p->info == _info) {
             pred->next = p->next;
             t = true;   
	  }
          pred = p;
          p = p->next;
       }
  }
  return t;
}

template<class T>
bool Insieme<T>::sottoinsieme(const Insieme<T>& _i) const{ //_i sottoins dell'ins d'invoc.
  bool b = true;
  smartp q, p = _i.first;
  while(p != 0 && b) {
    q = first;
    b = false;
    while(q != 0 && !b) {
       if(p->info == q->info) b = true;    
       q = q->next;
    }
    p = p->next;
  }
  return b;
}


template<class T>
bool Insieme<T>::operator==(const Insieme<T>& _i) {
  bool b = true;
  smartp q, p = _i.first;
  if(size() != _i.size()) return !b;  
  while(p != 0  && b) {
     b = false;
     q = first;
     while(q != 0 && !b) {
         if(q->info == p->info)  b = true;
	 q = q->next;
     }
     p = p->next;
  }
  return b;
}

template<class T>
bool Insieme<T>::operator!=(const Insieme<T>& _i) {
  bool b = true;
  smartp q, p = _i.first;
  if(size() != _i.size()) return b; 
  while(p != 0  && b) {
     b = false;
     q = first;
     while(q != 0 && !b) {
         if(q->info == p->info)  b = true;
	 q = q->next;
     }
     p = p->next;
  }
  return !b; 
}

template<class T>
Insieme<T> Insieme<T>::operator+(const Insieme<T>& _i){
  smartp q = _i.first;
  while(q != 0) {
    this->add(q->info);
    q = q->next;
  }
  return *this;
}

template<class T>
Insieme<T> Insieme<T>::operator-(const Insieme<T>& _i){
  smartp q = _i.first;
  while(q != 0) {
    this->remove(q->info);
    q = q->next;
  }
  return *this;
}

template<class T>
const char* Insieme<T>::write() const { 
  string str, cpl; 
  smartp p = first; 
  while(p != 0) {
    cpl = string(p->info.write());  //coppie
    str = str + cpl;     
    p = p->next; 
    if(p != 0) str.push_back(',');  //virgola dopo ogni elem 
  }
  str.push_back('}');
  str = '{' + str;
  return str.c_str();
}


template<class T>
const char* Insieme<T>::write_I() const { //stampa Insieme<char> 
  string str; 
  smartp p = first; 
  while(p != 0) { 
    str.push_back(p->info);   
    p = p->next; 
    if(p != 0) str.push_back(',');  //virgola dopo ogni elem 
  }
  str.push_back('}');
  str = '{' + str;
  return str.c_str();
}


#endif
