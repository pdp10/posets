#include "Catena.h"

string Catena::nome = "Catena ";

Catena::Catena(): Poset() {}

Catena::Catena(Relazione _R): Poset() {   
    Poset P(_R);
    if(P.catena()) {     
      Insieme<char>::smartp p = _R.getIns().first;
      Insieme<Coppia<char> >::smartp q = _R.getInsCop().first;
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

/*Dal gcc 3.3.3 da' problemi!
Catena::Catena(Poset _P): Poset() {
   if(_P.catena()) {
      Insieme<char>::smartp p = _P.getIns().first;                                   Insieme<Coppia<char> >::smartp q = _P.getInsCop().first;
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
*/

Catena::Catena(const int& _n): Poset() {
   if(_n > 1 && _n < 94){ 
       for(int i=1; i<_n; i++)
	 add(32+i, 33+i);      // parte dai char ! (33) e " (34)//l'ultimo char possibile e' '~'
       reflex_closure();
       trans_closure();
   }
}


//come su Poset ma ci si arresta subito appena trovati
/*Algoritmo:
-calcola per ogni elemento k di S, l'insieme dei suoi successori.(succ_k)
- se esiste almeno 1 elemento di S, eccetto k stesso, che compare in succ_k, allora k non e' massimale, altrimenti lo e' */   


Insieme<char> Catena::massimali(const Insieme<char>& S) const {
   Insieme<char>::smartp k, q, p = S.first;
   Insieme<char> massimali;
   if(I.sottoinsieme(S)) {
       bool presente = true;
       while(p != 0 && presente) {                          // differenza tra catena e Poset
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
	   else p = p->next;
       }
   }
   return massimali;
}

//analoga a massimali ma considera pred(p->info) anziche' post(p->info) 
Insieme<char> Catena::minimali(const Insieme<char>& S) const {
   Insieme<char>::smartp k, q, p = S.first;
   Insieme<char> minimali;
   if(I.sottoinsieme(S)) {
       bool presente = true;
       while(p != 0 && presente) {
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
	   else p = p->next;
       }
   }
   return minimali;
}

//come massimali() di poset tranne che si arresta subito appena trovato un massimale
char Catena::top() const {
   Insieme<char>::smartp p = I.first;
   Insieme<Coppia<char> >::smartp q;
   char top = ' ';
   bool presente = true;
   while(p != 0 && presente) {
        presente = false;
        q = R.first;
	while(q != 0 && !presente) 
	     if(p->info == q->info.read1() && q->info.read1() != q->info.read2() )
	          presente = true;
	     else q = q->next;
	if(!presente)  top = p->info;
	else p = p->next;
   }
   return top;
}


char Catena::bottom() const {
   Insieme<char>::smartp p = I.first;
   Insieme<Coppia<char> >::smartp q;
   char bottom = ' ';
   bool presente = true;
   while(p != 0 && presente) {
        presente = false;
        q = R.first;
	while(q != 0 && !presente) 
	     if(p->info == q->info.read2() && q->info.read1() != q->info.read2() )  //esclude coppie riflessive
	          presente = true;
	     else q = q->next;
	if(!presente)  bottom = p->info;
	else p = p->next;
   }
   return bottom;
}

Insieme<char> Catena::massimali() const{
  Insieme<char> massimale;
  char max = top();
  if(max != ' ') massimale.add(max);   //esclude il simbolo di "mancanza di top"
  return massimale;
}

Insieme<char> Catena::minimali() const {
  Insieme<char> minimale;
  char min = bottom();
  if(min != ' ') minimale.add(min);
  return minimale;
}

int Catena::livello() const{  return I.size(); }


Catena::~Catena() {}

string Catena::get_nome() const { return nome; }

ostream& operator<<(ostream& os, const Catena& _c) {
  os << "Dominio Catena = " << _c.getIns() 
     << "\nRelazione d'ordine = " << _c.getInsCop() << endl; 
  return os;
}
