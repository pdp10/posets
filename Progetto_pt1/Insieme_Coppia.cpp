#include"Insieme_Coppia.h"
#include"Coppia.h"
#include<iostream>
using namespace std;


//CLASS SMARTP
Insieme_Coppia::smartp::smartp(nodo* _point): point(_point) {
  if(point) point->reference++; }
Insieme_Coppia::smartp::smartp(const smartp& _sp): point(_sp.point) {
  if(point) point->reference++; }
Insieme_Coppia::smartp::~smartp() {
  if(point) {
    point->reference--;
    if(point->reference == 0)
      delete point;
  }
}

Insieme_Coppia::smartp& Insieme_Coppia::smartp::operator=(const smartp& _sp) {
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

Insieme_Coppia::nodo& Insieme_Coppia::smartp::operator*() const {
  return *point; }
Insieme_Coppia::nodo* Insieme_Coppia::smartp::operator->() const {
  return point; }
bool Insieme_Coppia::smartp::operator==(smartp _sp) const {
  return point == _sp.point; }
bool Insieme_Coppia::smartp::operator!=(smartp _sp) const {
  return point != _sp.point; }
  


//CLASS NODO
Insieme_Coppia::nodo::nodo(): cp(0,0), next(0), reference(0) {}
Insieme_Coppia::nodo::nodo(Coppia& _cp, const smartp& _sp): 
                         cp(_cp), next(_sp), reference(0) {}





//FUNZIONI AUSILIARIE
 int Insieme_Coppia::size() const { 
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

 bool Insieme_Coppia::see(const Coppia& x) const {  // scorre l'insieme e ritorna true se x e' presente, false altrimenti
   if(first == 0) return false;       // insieme vuoto        
   smartp p = first;
   bool t = false;
   while(p != 0 && !t) 
     {if( (p->cp).read1()== x.read1() && (p->cp).read2()== x.read2() ) 
         t = true;
      p = p->next;}
   if(t) return true;
   return false;
 } 





//CLASS INSIEME_COPPIA
ostream& operator<<(ostream& os, const Insieme_Coppia& ii) {
  if(ii.size() == 0) return os << "Insieme vuoto" << endl; 
  else {
    Insieme_Coppia::smartp sp = ii.first;
    os << "\nInsieme:\n" <<'{'<< sp->cp;
    while(sp->next != 0) {
      os <<',' << sp->next->cp;
      sp = sp->next;
    }
  os << '}';
  }
  return os;
}



bool Insieme_Coppia::add(const Coppia& _cp) {
  if(see(_cp))  return false;              // _cp e' presente
   nodo* p = new nodo;
  p->next = first;
  first = p;
  p->cp = _cp;
  return true;
}

bool Insieme_Coppia::remove(const Coppia& _cp) {
  if(first == 0) {
    cout<<"\nL'insieme e' vuoto\n";
    return false;
  }
  smartp p = first;
  if(p != 0 && p->next == 0){              // caso 1 elem
    if( p->cp.read1() == _cp.read1() &&  p->cp.read2() == _cp.read2() )  
      { first = 0;
      return true; }
    else { cout <<"\nCoppia non presente\n";
          return false;
    }
  }
  bool t = false;
  if(p->next != 0) {     //caso piu' di 1 elemento 
   smartp pred = p;
    p = p->next;
    if( pred->cp.read1()== _cp.read1() &&  pred->cp.read2()== _cp.read2() )  
         { first = p; return true; }
    else {
       while(p != 0 && !t)  {
	 if( (p->cp).read1() == _cp.read1() &&  (p->cp).read2()== _cp.read2() ) {
               pred->next = p->next;
               t = true;   
	  }
        pred = p;
        p = p->next;
       }
    }
  if(t) return true;
  cout <<"\nCoppia non presente\n";
  return false;
  }
}


bool Insieme_Coppia::operator==(const Insieme_Coppia& _ii) {
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
          if(q->cp == p->cp) {
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


bool Insieme_Coppia::operator!=(const Insieme_Coppia& _ii) {
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
          if(q->cp == p->cp) {
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

Insieme_Coppia Insieme_Coppia::operator+(const Insieme_Coppia& _ii){
  Insieme_Coppia x;
  smartp p = first;
  smartp q = _ii.first;
  while(p != 0) { 
    Coppia a(p->cp.read1(), p->cp.read2());
    x.add(a);
    p = p->next;
  }
  while(q != 0) {
    Coppia b(p->cp.read1(), p->cp.read2());
    x.add(b);
    q = q->next;
  }
  return x;
}

