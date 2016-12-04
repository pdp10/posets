#include "Coppia.h"
#include "Insieme_int.h"
#include "Insieme_Coppia.h"
#include "Relazione.h"
#include <iostream>

using std::cout; using std::endl;

main() {
  Coppia c1(0,1); Coppia c2(1,2);
  
  cout << (c1==c2) << endl; // stampa: 0
 
  Insieme_int ins1;
  cout << ins1 << endl; // stampa: @
  
  ins1.add(3);
  cout << ins1 << endl; // stampa: {3}
  cout << ins1.add(3) << ", " << ins1 << endl; // stampa: 0, {3}

  ins1.remove(3);
  cout << ins1 << endl; // stampa: @
  cout << ins1.remove(3) << ", " << ins1 << endl; // stampa: 0, @

  Insieme_int ins2;
  ins2.add(1);
  ins2.add(2);
  ins2.add(3);
  cout << ins2 << endl; // stampa: {1,2,3}
  
  cout << Relazione() << endl; // stampa: 
  // dominio = @
  // relazione = @ 
  
  Insieme_int dominio; 
  for(int k=1; k<6; k++) dominio.add(k);
  Insieme_Coppia coppie;
  coppie.add(Coppia(1,2));
  coppie.add(Coppia(2,1));
  Relazione rel(dominio,coppie); 
  cout << rel << endl; // stampa:
  // dominio = {1,2,3,4,5}
  // relazione = {(1,2),(2,1)}
 
  cout << rel*rel << endl; // stampa:
  // dominio = {1,2,3,4,5}
  // relazione = {(1,1),(2,2)}
  
  cout << rel.inversa() << endl; // stampa:
  // dominio = {1,2,3,4,5}
  // relazione = {(1,2),(2,1)}
  
  cout << rel.total() << endl; // stampa: 0

  Insieme_int dominio2;
  for(int k=1; k<3; k++) dominio2.add(k);
  Relazione rel2(dominio2,coppie);
  cout << rel2.total() << endl; // stampa: 1

  cout << rel.post(1) << endl; // stampa: {2}
  
  Relazione rel3(rel);
  rel3.add(2,3);  

  rel.trans_closure();
  cout << rel << endl; // stampa:
  // dominio: {1,2,3,4,5}
  // relazione: {(1,2),(2,1),(1,1),(2,2)}

  cout << rel3 << endl; // stampa:
  // dominio: {1,2,3,4,5}
  // relazione: {(1,2),(2,1),(2,3)}

  rel3.reflex_closure();
  cout << rel3 << endl; // stampa:
  // dominio: {1,2,3,4,5}
  // relazione: {(1,2),(2,1),(2,3),(1,1),(2,2),(3,3),(4,4),(5,5)}

  rel.reflex_closure();
  cout << rel << endl; // stampa:
  // dominio: {1,2,3,4,5}
  // relazione: {(1,2),(2,1),(1,1),(2,2),(3,3),(4,4),(5,5)}

  rel3.trans_closure();
  cout << rel3 << endl; // stampa:
  // dominio: {1,2,3,4,5}
  // relazione: {(1,2),(2,1),(2,3),(1,1),(2,2),(3,3),(4,4),(5,5),(1,3)}

  rel3.remove(3,3);
  cout << rel3 << endl; // stampa:
  // dominio: {1,2,3,4,5}
  // relazione: {(1,2),(2,1),(2,3),(1,1),(2,2),(4,4),(5,5),(1,3)}

  rel3.add(6,5);
  cout << rel3 << endl; // stampa:
  // dominio: {1,2,3,4,5,6}
  // relazione: {(1,2),(2,1),(2,3),(1,1),(2,2),(4,4),(5,5),(1,3),(6,5)}
   
  cout << rel(1,2) << endl; // stampa: 1
  cout << rel(4,9) << endl; // stampa: 0


}
