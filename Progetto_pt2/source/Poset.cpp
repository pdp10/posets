#include"Poset.h"

string Poset::nome = "Poset ";


Poset::Poset(): Relazione() {}

Poset::Poset(Relazione _R): Relazione(){
  Insieme<Coppia<char> >::smartp q = _R.getInsCop().first;
  if(_R.acyclic()) {
      Insieme<char>::smartp p = _R.getIns().first;
      while(p != 0) {
	   I.add(p->info);
	   p = p->next;
      }
      while(q != 0) {
	   R.add(q->info);
	   q = q->next;
      }
      reflex_closure();   
      trans_closure();
  }
}


bool Poset::add(const char& x, const char& y) {
  Coppia<char> c(x,y);
  if (R.see(c))
    return false;
  else {
    I.add(x);
    I.add(y);
    R.add(c);
    if(!acyclic()) { remove(x,y); return false;   }
    return true;
  }
}


/*Algoritmo:
-calcola per ogni elemento k di S, l'insieme dei suoi successori.(succ_k)
- se esiste almeno 1 elemento di S, eccetto k stesso, che compare in succ_k, allora k non e' massimale, altrimenti lo e' */

Insieme<char> Poset::massimali(const Insieme<char>& S) const {
   Insieme<char>::smartp k, q, p = S.first;
   Insieme<char> massimali;
   if(I.sottoinsieme(S)) {
       bool presente;
       while(p != 0) {
  	   Insieme<char> succ_k = post(p->info);       //insieme dei successori di p->info
	   q = S.first;
	   presente = false;
	   while(q != 0 && !presente) {
	        k = succ_k.first;
		while(k != 0 && !presente) 
		   if(q->info == k->info && q->info != p->info)
		        presente = true;
		   else k = k->next;
		q = q->next; 
	   }
	   if(!presente)  massimali.add(p->info);
	   p = p->next;
       }
   }
   return massimali;
}

//analoga a massimali ma considera pred(p->info) anziche' post(p->info) 
Insieme<char> Poset::minimali(const Insieme<char>& S) const {
   Insieme<char>::smartp k, q, p = S.first;
   Insieme<char> minimali;
   if(I.sottoinsieme(S)) {
       bool presente;
       while(p != 0) {
  	   Insieme<char> pred_k = pred(p->info);       //insieme dei successori di p->info
	   q = S.first;
	   presente = false;
	   while(q != 0 && !presente) {
	        k = pred_k.first;
		while(k != 0 && !presente) 
		   if(q->info == k->info && q->info != p->info)
		        presente = true;
		   else k = k->next;
		q = q->next; 
	   }
	   if(!presente)  minimali.add(p->info);
	   p = p->next;
       }
   }
   return minimali;
}


/*Algoritmo:
Per ogni elemento del dominio si verifica se esso e' presente come primo elemento della relazione del poset. Se e' presente, non e' un massimale, altrimenti lo e'
*/

Insieme<char> Poset::massimali() const {
   Insieme<char> massimali;
   Insieme<char>::smartp p = I.first;
   Insieme<Coppia<char> >::smartp q;
   bool presente;
   while(p != 0) {
        presente = false;
        q = R.first;
	while(q != 0 && !presente) 
	     if(p->info == q->info.read1() && q->info.read1() != q->info.read2() )  //ossia non e' coppia riflessiva
	          presente = true;
	     else q = q->next;
	if(!presente)  massimali.add(p->info);
	p = p->next;
   }
   return massimali;
}


Insieme<char> Poset::minimali() const {
   Insieme<char> minimali;
   Insieme<char>::smartp p = I.first;
   Insieme<Coppia<char> >::smartp q;
   bool presente;
   while(p != 0) {
        presente = false;
        q = R.first;
	while(q != 0 && !presente) 
	     if(p->info == q->info.read2() && q->info.read1() != q->info.read2() )  // ossia non e' coppia riflessiva
	          presente = true;
	     else q = q->next;
	if(!presente)  minimali.add(p->info);
	p = p->next;
   }
   return minimali;
}




//OPTIONAL

Relazione Poset::copertura() const {
  Relazione copertura(I, R);
  copertura.remove_reflex_closure();
  copertura.remove_trans_closure();
  return copertura;
}


int Poset::livello() const  {
  Insieme<char> ins_min = minimali(), ins_dom = I;
  int livello = 0;
  while(!ins_min.empty())  {
      livello ++;
      ins_dom = ins_dom - ins_min;
      ins_min = minimali(ins_dom);
  }
  return livello;
}


Insieme<char> Poset::livello(const int& n) const  {
  Insieme<char> ins_min = minimali(), ins_dom = I, ins_livello;
  int livello = 0;
  if(!ins_min.empty() && livello < n) {
    livello++;
    while(!ins_min.empty() && livello < n)  {
        livello ++;
        ins_dom = ins_dom - ins_min;
        ins_min = minimali(ins_dom);
    }
    ins_livello = ins_min;
  }
  return ins_livello;
}


bool Poset::catena() const {
  if(I.size() == livello()) 
    return true;
  return false;
}

Poset::~Poset() {}

string Poset::get_nome() const { return nome; }

ostream& operator<<(ostream& os, const Poset& pos){
  os << "Dominio Poset = " << pos.getIns()
     << "\nRelazione d'ordine = " << pos.getInsCop() << endl;
  return os;
}

