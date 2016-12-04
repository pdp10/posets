#include"Insieme_int.h"
#include"Insieme_Coppia.h"
#include"Coppia.h"
#include"Relazione.h"
#include<iostream>
using namespace std;


Relazione::Relazione(): I(Insieme_int()), R(Insieme_Coppia()) {}
Relazione::Relazione(const Insieme_int& _I, const Insieme_Coppia& _R) {
  bool test = true;
  Insieme_Coppia::smartp p = _R.first;
  while (p != 0 && test) {
    if (_I.see(p->cp.read1()) && _I.see(p->cp.read2()))
      test=true;
    else 
      test = false;
    p = p->next;
  }
    if (test){
      I = Insieme_int(_I);
      R = Insieme_Coppia(_R);
    }
}

   
    
bool Relazione::add(int x, int y) {
  Coppia c(x,y);
  if (R.see(c))
    return false;
  else {
    I.add(x);
    I.add(y);
    return R.add(c);	
  }
}


bool Relazione::remove(int x,int y){
  Coppia c(x, y);
  return R.remove(c);
}

Relazione Relazione::operator*(const Relazione& _R){
  Insieme_Coppia::smartp p = R.first;
  Insieme_Coppia::smartp q = _R.R.first;
  Relazione r;
  r.I = I + _R.I;
  bool test = false;
  if(p == 0 || q == 0)  cout<< " \nAlmeno uno dei due insiemi e' vuoto";  
  else { 
    while(p != 0) {
      while(q != 0 && !test) {
	if(p->cp.read2() == q->cp.read1()){
	  Coppia c(p->cp.read1(), q->cp.read2());
	  r.R.add(c);
	  test = true;
	}
	q = q->next;
      }
      test = false;
      p = p->next;
      q = _R.R.first;
    }
  }
  return r;
}

Relazione Relazione::inversa() {
  int temp1;
  int temp2;
  Relazione inversa;
  inversa.I=I;
  Insieme_Coppia::smartp p = R.first;
  while (p !=0) {
    temp1 = p->cp.read1();
    temp2 = p->cp.read2();
    Coppia c(p->cp.read1(), p->cp.read2());
    c = Coppia(temp2,temp1);
    inversa.R.add(c);
    p = p->next;
  }
  return inversa;
}

bool Relazione::operator()(int x,int y){
  Coppia cpa(x,y);
  return R.see(cpa); 
}


Insieme_int Relazione::post(int x) {
  Insieme_int i;
  Insieme_Coppia::smartp p = R.first;
  if(p == 0) { cout << "\nInsieme d'invocazione vuoto"; }
  else {
    while(p != 0) {
          if(p->cp.read1() == x )
        	i.add(p->cp.read2());
	  p = p->next;
    }
  }
  return i;
}
        



bool Relazione::total(){
  Insieme_int::smartp p = I.first;
  Insieme_Coppia::smartp q = R.first;
  bool test1 = true;
  bool test2 = false;
   if(p == 0 || q == 0) {
         cout<< " \nAlmeno uno dei due insiemi e' vuoto";  
	 test1 = false;
  }
  else {  
    while(p != 0 && test1){
      while(q != 0 && !test2){
	if( p->num == q->cp.read1())
	  test2 = true;
	q = q->next;
      }
    test1 = test2;
    test2 = false;
    q = R.first;
    p = p->next; 
    }}
   return test1;
}



void Relazione::trans_closure() {
  bool test1;
  Coppia c;
  Insieme_Coppia::smartp p = R.first;
  Insieme_Coppia::smartp q = R.first;
  while (p != 0) {
    test1 = false;
    while (q !=0 && !test1) {
      if(p->cp.read1() == q->cp.read2()){
	c = Coppia(p->cp.read1(), p->cp.read2());
	R.add(c);
	test1=true;
      }
      q = q->next;
    }
    p = p->next;
    q = R.first;
  }
}

void Relazione::reflex_closure() {
  Coppia c;
  Insieme_int::smartp p = I.first;
  while (p != 0){
    c = Coppia(p->num, p->num);
    R.add(c);
    p = p->next;
  }

}



ostream& operator<<(ostream& os, const Relazione& r){
  os << "DOMINIO = " <<r.I;
  os << "\nRELAZIONE = " << r.R << endl;
  return os;
}

