#include"Insieme_int.h"
#include<iostream>
using namespace std;


//CLASS SMARTP
Insieme_int::smartp::smartp(nodo* _point): point(_point) {
  if(point) point->reference++; }
Insieme_int::smartp::smartp(const smartp& _sp): point(_sp.point) {
  if(point) point->reference++; }
Insieme_int::smartp::~smartp() {
  if(point) {
    point->reference--;
    if(point->reference == 0)
      delete point;
  }
}

Insieme_int::smartp& Insieme_int::smartp::operator=(const smartp& _sp) {
  if(this != &_sp) {
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

Insieme_int::nodo& Insieme_int::smartp::operator*() const {
  return *point; }
Insieme_int:: nodo* Insieme_int::smartp::operator->() const {
  return point; }
bool Insieme_int::smartp::operator==(smartp _sp) const {
  return point == _sp.point; }
bool Insieme_int::smartp::operator!=(smartp _sp) const {
  return point != _sp.point; }
  


//CLASS NODO
Insieme_int::nodo::nodo(): num(0), next(0), reference(0) {}
Insieme_int::nodo::nodo(int& _num, const smartp& _sp): 
                         num(_num), next(_sp), reference(0) {}





//FUNZIONI AUSILIARIE
 int Insieme_int::size() const { 
   int count = 0;
   smartp p = first;
   if(p == 0) { return count;}
   count++;
   while(p->next != 0) {
     count++;
     p = p->next;
   }
   return count;
 }

 bool Insieme_int::see(int x) const {               // scorre l'insieme e ritorna true se x e' presente, false altrimenti
   if(first == 0) return false;                        // insieme vuoto   
      smartp p = first;
   bool t = false;
   while(p != 0 && !t) 
     {if(p->num == x) 
         t = true;
      p = p->next;}
   if(t) return true;
   return false;
 } 





//CLASS INSIEME_INT
ostream& operator<<(ostream& os, const Insieme_int& ii) {
  if(ii.size() == 0) return os << "Insieme vuoto" << endl; 
  else {
    Insieme_int::smartp sp = ii.first;
    os << "\nInsieme:\n" <<'{'<< sp->num;
    while(sp->next != 0) {
      os <<',' << sp->next->num;
      sp = sp->next;
    }
  os << '}';
  }
  return os;
}



bool Insieme_int::add(int _num) {
  if(see(_num))  return false;              // _num e' presente
   nodo* p = new nodo;
  p->next = first;
  first = p;
  p->num = _num;
  return true;
}

bool Insieme_int::remove(int _num) {
  if(first == 0) {
    cout<<"\nL'insieme e' vuoto\n";
    return false;
  }
  smartp p = first;
  if(p != 0 && p->next == 0){              // caso 1 elem
    if(p->num == _num)  
      { first = 0;
      return true; }
    else { cout <<"\nElemento non presente\n";
          return false;
    }
  }
  bool t = false;
  if(p->next != 0) {     //caso piu' di 1 elemento 
   smartp pred = p;
    p = p->next;
    if(pred->num == _num)
        { first = p; return true; }
    else {
       while(p != 0 && !t)  {
          if(p->num == _num) {
             pred->next = p->next;
             t = true;   
	  }
        pred = p;
        p = p->next;
       }
    }
  if(t) return true;
  cout <<"\nElemento non presente\n";
  return false;
  }
}


bool Insieme_int::operator==(const Insieme_int& _ii) {
  bool test = true;
  bool test2 = true;
  if(size() != _ii.size()) { // insiemi devono avere = taglia
    cout<<"\nGli insiemi hanno differente numero di elementi\n";
    return !test;
  }
  else { 
    if(first != 0) {                       // insiemi non vuoti!!
      bool cc = 0;
      smartp p = _ii.first;
      smartp q = first;
      while(p != 0  && test) {
        while(q != 0 && test2) {
          if(q->num == p->num) {
                  cc = 1;            // elemento presente
		  test2 = false;
	  }
          q = q->next;
	}
	test2 = true;
	if(cc == 0) test = false;  //elem presente in A, ma non in B
        p = p->next;
	q = first;
	cc = 0;
      }
    }
  } 
  return test;
}


bool Insieme_int::operator!=(const Insieme_int& _ii) {
  bool test = true;
  bool test2 = true;
  if(size() != _ii.size()) { // insiemi devono avere = taglia
    cout<<"\nGli insiemi hanno differente numero di elementi\n";
    return test;
  }
  else { 
    if(first != 0) {                       // insiemi non vuoti!!
      bool cc = 0;
      smartp p = _ii.first;
      smartp q = first;
      while(p != 0  && test) {
        while(q != 0 && test2) {
          if(q->num == p->num) {
                  cc = 1;            // elemento presente
		  test2 = false;
	  }
          q = q->next;
	}
	test2 = true;
	if(cc == 0) test = false;  //elem presente in A, ma non in B
        p = p->next;
	q = first;
	cc = 0;
      }
    }
  } 
  return !test;
}

Insieme_int Insieme_int::operator+(const Insieme_int& _ii){
  Insieme_int x;
  smartp p = first;
  smartp q = _ii.first;
  while(p != 0) { 
    x.add(p->num);
    p = p->next;
  }
  while(q != 0) {
    x.add(q->num);
    q = q->next;
  }
  return x;
}

