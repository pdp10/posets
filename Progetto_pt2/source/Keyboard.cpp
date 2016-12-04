#include "Keyboard.h"
#include "Progetto_pt2.h"
#include "Insieme.h"
#include "Coppia.h"
#include "Relazione.h"
#include "Poset.h"
#include "Catena.h"
#include "Temp.h"
#include <string>
#include <typeinfo>
#include <iostream>
using namespace std;


enum  { INPUTREL=1, 
	CREAPOSET, 
	CREACATENA, 
	MINIMALI, 
	MASSIMALI, 
	COPERTURA };

Keyboard::Keyboard(wxWindow* parent, Progetto_pt2* app):  wxPanel(parent, -1, wxPoint(0,0)), main(app) {
 
      box = new wxBoxSizer(wxHORIZONTAL);    

      inputrel = new wxButton(this,   INPUTREL,   "Input di Relazione", wxDefaultPosition, wxSize(-1,-1));
      creaposet = new wxButton(this,  CREAPOSET,  "Crea Poset",         wxDefaultPosition, wxSize(-1,-1));
      creacatena = new wxButton(this, CREACATENA, "Crea Catena",        wxDefaultPosition, wxSize(-1,-1));
      minimali = new wxButton(this,   MINIMALI,   "Minimali",           wxDefaultPosition, wxSize(-1,-1));
      massimali = new wxButton(this,  MASSIMALI,  "Massimali",          wxDefaultPosition, wxSize(-1,-1));
      copertura = new wxButton(this,  COPERTURA,  "Copertura",          wxDefaultPosition, wxSize(-1,-1));


      box->Add(inputrel,    1, wxALIGN_CENTER|wxALL, 3);
      box->Add(creaposet,   1, wxALIGN_CENTER|wxALL, 3);
      box->Add(creacatena,  1, wxALIGN_CENTER|wxALL, 3);
      box->Add(minimali,    1, wxALIGN_CENTER|wxALL, 3);
      box->Add(massimali,  1, wxALIGN_CENTER|wxALL, 3);
      box->Add(copertura,  1, wxALIGN_CENTER|wxALL, 3);

      //settaggio definitivo
      SetSizer(box);
      box->Fit(this);
}
  
void Keyboard::inputrel_evento() {
      string str = main->get_string();
      Temp t;
      Relazione* rel = 0;
      if(t.parsing(str)) {
           Insieme<Coppia<char> > R = t.create_str(str);
           rel = new Relazione(R);
      }
      main->set_current(rel);
      main->set_log_status(" ");
}

void Keyboard::creaposet_evento() {
      Relazione* rel = main->current();
      if(rel) {
          Poset* pos = new Poset(*rel);
          main->set_current(pos);
      }
      else main->set_current(rel);  // caso di errore
      main->set_log_status(" ");
}

void Keyboard::creacatena_evento() {
      Relazione* rel = main->current();
      if(rel) {
           Catena* cat = new Catena(*rel);
           main->set_current(cat);
      }
      else main->set_current(rel);   //caso errore
      main->set_log_status(" ");
}

void Keyboard::minimali_evento() {  
      Relazione* rel = main->current(); 
      if(rel) {
          Poset* pos = dynamic_cast<Poset*>(rel);
          if(pos) {
              Insieme<char>* set = new Insieme<char>(pos->minimali());
              main->set_value(set);
	  }
	  else main->set_log_status("Minimali non e' implementato in Relazione");
      }
      else main->set_current(rel);      //caso di errore
}


void Keyboard::massimali_evento() { 
      Relazione* rel = main->current(); 
      if(rel) {
          Poset* pos = dynamic_cast<Poset*>(rel);
          if(pos) {
              Insieme<char>* set = new Insieme<char>(pos->massimali());
              main->set_value(set);
	  }
	  else main->set_log_status("Massimali non e' implementato in Relazione");
      }
      else main->set_current(rel);          //caso di errore
}


void Keyboard::copertura_evento() {
      Relazione* rel = main->current(); 
      if(rel) {
 	  Poset pos(*rel);
          rel = new Relazione(pos.copertura());
          main->set_current(rel);
      }
      else main->set_current(rel);    //caso di errore
}



BEGIN_EVENT_TABLE(Keyboard,  wxPanel)
      EVT_BUTTON(INPUTREL,    Keyboard::inputrel_evento)
      EVT_BUTTON(CREAPOSET,   Keyboard::creaposet_evento)
      EVT_BUTTON(CREACATENA,  Keyboard::creacatena_evento)
      EVT_BUTTON(MINIMALI,    Keyboard::minimali_evento)
      EVT_BUTTON(MASSIMALI,   Keyboard::massimali_evento)
      EVT_BUTTON(COPERTURA,   Keyboard::copertura_evento)
END_EVENT_TABLE()
