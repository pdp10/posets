#ifndef PROGETTO_PT2_H
#define PROGETTO_PT2_H
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
   #include "wx/wx.h"
#endif

#include <iostream>
#include "Coppia.h"
#include "Insieme.h"
#include "Relazione.h"
#include "Poset.h"
#include "Catena.h"
#include "Keyboard.h"
#include "Menu.h"
#include "Temp.h"
#include <string>
#include <typeinfo>
using namespace std;


class Progetto_pt2: public wxApp {
  public:
      virtual bool OnInit();

      const char* get_string();
      const char* get_string_I();  //per l'input di insiemi o valori
      const char* get_string_out1(); //restituisce l'output
      const char* get_string_out2();
      Relazione* current();
      Insieme<char>* i_current();
      void set_current(Relazione*);
      void set_value(Insieme<char>*);
      void paste_string(string);
      void set_open_file(string,string,string,string);
      void set_log_status(string);
      void clean_all();
      void msg_error();
      void msg_error_I();

  private:
      Relazione* cur;  
      Insieme<char>* i_cur;
      string stato;

      Menu* frame;
      Keyboard* keyb;
      wxStaticText* st1;         
      wxTextCtrl* input;          //legge relazioni
      wxStaticText* st2;
      wxTextCtrl* input_fun;      //legge insiemi
      wxStaticText* st3;
      wxTextCtrl* output;         
      wxStaticText* st4;
      wxTextCtrl* output_fun;     //per i metodi

};

#endif
