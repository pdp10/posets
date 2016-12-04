#ifndef TEMP_H
#define TEMP_H

#include <iostream>
#include "Insieme.h"
#include "Coppia.h"
#include "Relazione.h"
#include "Poset.h"
#include "Catena.h"
#include <string>
using namespace std;

class Temp {
  private:
      int somma(int*, int);
      void calcola(int*, char, int&);
  public:
      Temp();
      Insieme<Coppia<char> > create_str(const string&); 
      Insieme<char> create_I_str(const string&);
      int create_single(const string&);
      bool parsing(const string&);
      bool parsing_I(const string&);
      bool parsing_single(const string&); 
};

#endif
