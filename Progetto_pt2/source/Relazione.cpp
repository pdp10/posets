#include"Relazione.h"

string Relazione::nome = "Relazione";

Relazione::Relazione(): I(Insieme<char>()), R(Insieme<Coppia<char> >()) {}
Relazione::Relazione(const Insieme<char>& _I, const Insieme<Coppia<char> >& _R) {
  bool test = true;
  Insieme<Coppia<char> >::smartp q = _R.first;
  while (q != 0 && test) {
    if (_I.see(q->info.read1()) && _I.see(q->info.read2()))
      test=true;
    else 
      test = false;
    q = q->next;
  }
    if (test){
      Insieme<char>::smartp p = _I.first;
      q = _R.first;
      while(p != 0) {
	I.add(p->info);
	p = p->next;
      }
      while(q != 0) {
	R.add(q->info);
	q = q->next;
      }
    }
}

// costruttore di relazione a partire dal solo Insieme<Coppia<T> >
Relazione::Relazione(const Insieme<Coppia<char> >& _R): 
                                     I(), R(Insieme<Coppia<char> >(_R)) {
  Insieme<Coppia<char> >::smartp q = _R.first;
  while (q != 0) {
    I.add(q->info.read1());
    I.add(q->info.read2());
    q = q->next;
  }
}



bool Relazione::add(const char& x, const char& y) {
  Coppia<char> c(x,y);
  if (R.see(c))
    return false;
  else {
    I.add(x);
    I.add(y);
    return R.add(c);	
  }
}



bool Relazione::remove(const char& x, const char& y){
  Coppia<char> c(x, y);
  Insieme<Coppia<char> >::smartp p = R.first;
  bool r = R.remove(c), trov_x = false, trov_y = false;
  while(p != 0 && (!trov_x || !trov_y) ) {//elimina x o y nel dominio se x o y non compaiono piu' in R
    if(x == p->info.read1() || x == p->info.read2())
       trov_x = true;
    if(y == p->info.read1() || y == p->info.read2())
       trov_y = true;
    p = p->next;
  }
  if(!trov_x) I.remove(x);
  if(!trov_y) I.remove(y);
  return r;
}



Relazione Relazione::operator*(const Relazione& _R){
  Insieme<Coppia<char> >::smartp p = R.first;
  Insieme<Coppia<char> >::smartp q = _R.R.first;
  Relazione r;
  r.I = I + _R.I;
  bool test = false;
  if(p == 0 || q == 0)  cout<< " \nAlmeno uno dei due insiemi e' vuoto\n";  
  else { 
    while(p != 0) {
      while(q != 0 && !test) {
	if(p->info.read2() == q->info.read1()){
	  Coppia<char> c(p->info.read1(), q->info.read2());
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
  Relazione inversa;
  Coppia<char> c;
  inversa.I=I;
  Insieme<Coppia<char> >::smartp p = R.first;
  while (p != 0) {
      c = Coppia<char>(p->info.read2(), p->info.read1());
      inversa.R.add(c);
      p = p->next;
  }
  return inversa;
}

bool Relazione::operator()(const char& x, const char& y){
   Coppia<char> cpa(x,y);
   return R.see(cpa); 
}

bool Relazione::total() const{
  Insieme<char>::smartp p = I.first;
  Insieme<Coppia<char> >::smartp q = R.first;
  bool test1 = true;
  bool test2 = false;
   if(p == 0 || q == 0) {
         cout<< " \nAlmeno uno dei due insiemi e' vuoto\n";  
	 test1 = false;
  }
  else {  
    while(p != 0 && test1){
      while(q != 0 && !test2){
	if( p->info == q->info.read1())
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
  Coppia<char> c;
  Insieme<Coppia<char> >::smartp q,p = R.first;
  while (p != 0) {
    q = R.first;      
    while (q != 0) {
      if(p->info.read2() == q->info.read1() ){
	c = Coppia<char>(p->info.read1(), q->info.read2());
	R.add(c);
      }
      q = q->next;
    }
    p = p->next;
  }
}

void Relazione::reflex_closure() {
  Coppia<char> c;
  Insieme<char>::smartp p = I.first;
  while (p != 0){
    c = Coppia<char>(p->info, p->info);
    R.add(c);
    p = p->next;
  }
}

//altrimenti tralascia delle coppie.
//P.es (6,9),(9,8),(3,7),(7,6).. tralascia (7,8)
//* perche' altrimenti se la reflex_closure non e' stata eliminata.. rimarra' alla fine soltanto questa..


void Relazione::remove_trans_closure() {  //per la copertura
  Insieme<Coppia<char> > Delete;          //conterra' tutte le coppie da eliminare
  Coppia<char> c;
  Insieme<Coppia<char> >::smartp q,p = R.first;
  while (p != 0) {
    q = R.first;      
    while (q != 0) {
      if(p != q && p->info.read2() == q->info.read1() &&
	 p->info.read1() != p->info.read2() && q->info.read1() != q->info.read2() )   //*evita le coppie della reflex_closure.
       {
	  c = Coppia<char>(p->info.read1(), q->info.read2());
  	  Delete.add(c);
       }
      q = q->next;
    }
    p = p->next;
  }
  p = Delete.first;
  while(p != 0) {    
    R.remove(p->info);
    p = p->next;
  }
}

void Relazione::remove_reflex_closure() {
  Insieme<Coppia<char> >::smartp p = R.first;
  Coppia<char> c;
  while (p != 0){
    if(p->info.read1() == p->info.read2()) {
      c = Coppia<char>(p->info.read1(), p->info.read2());
      R.remove(c);
    }
    p = p->next;
  }
}

Insieme<char> Relazione::post(const char& x) const{
  Insieme<char> i;
  Insieme<Coppia<char> >::smartp p = R.first;
  while(p != 0) {
          if(p->info.read1() == x )
        	i.add(p->info.read2());
	  p = p->next;
  }
  return i;
}

Insieme<char> Relazione::post_(const char& x) const{       //successori propri di x
  Insieme<char> i;
  Insieme<Coppia<char> >::smartp p = R.first;
  while(p != 0) {
          if(p->info.read1()==x  &&  p->info.read2()!=x)
        	i.add(p->info.read2());
	  p = p->next;
  }
  return i;
}

Insieme<char> Relazione::post2(const Insieme<char>& S) const{
  Insieme<char> succ;
  Insieme<char>::smartp p = S.first;
  while(p != 0) {
    succ = succ + post(p->info);
    p = p->next;
  }
  return succ;
}

Insieme<char> Relazione::post2_(const Insieme<char>& S) const{
  Insieme<char> succ;
  Insieme<char>::smartp p = S.first;
  while(p != 0) {
    succ = succ + post_(p->info);
    p = p->next;
  }
  return succ;
}

Insieme<char> Relazione::pred(const char& x) const{
  Insieme<char> i;
  Insieme<Coppia<char> >::smartp p = R.first;
  while(p != 0) {
          if(p->info.read2() == x )
        	i.add(p->info.read1());
	  p = p->next;
  }
  return i;
}

Insieme<char> Relazione::pred_(const char& x) const{       //successori propri di x
  Insieme<char> i;
  Insieme<Coppia<char> >::smartp p = R.first;
  while(p != 0) {
          if(p->info.read2()==x  &&  p->info.read1()!=x)
        	i.add(p->info.read1());
	  p = p->next;
  }
  return i;
}

Insieme<char> Relazione::pred2(const Insieme<char>& S) const{
  Insieme<char> pre;
  Insieme<char>::smartp p = S.first;
  while(p != 0) {
    pre = pre + pred(p->info);
    p = p->next;
  }
  return pre;
}

Insieme<char> Relazione::pred2_(const Insieme<char>& S) const{
  Insieme<char> pre;
  Insieme<char>::smartp p = S.first;
  while(p != 0) {
    pre = pre + pred_(p->info);
    p = p->next;
  }
  return pre;
}

bool Relazione::acyclic() {             
  Insieme<Coppia<char> >::smartp p = R.first;
  Insieme<char>::smartp q;
  bool acyclic = true;
  while(p != 0 && acyclic){
      Insieme<char> S = post_(p->info.read1()); //insieme successori propri di p->info
      q = S.first;
      while(q != 0){
	S = S + post(q->info);        
	q = q->next;                   
      }
      if(S.see(p->info.read1())) acyclic = false;
      else p = p->next;
  }
  return acyclic;
}


Insieme<char> Relazione::getIns() const {  return I; }

Insieme<Coppia<char> > Relazione::getInsCop() const { return R; }

string Relazione::get_nome() const { return nome; }

Relazione::~Relazione() {}


ostream& operator<<(ostream& os, const Relazione& r){
  os << "Dominio = " << r.I;
  os << "\nRelazione = " << r.R << endl;
  return os;
}
