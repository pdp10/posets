#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
   #include "wx/wx.h"
#endif



class Progetto_pt2;

class Keyboard: public wxPanel {
  public:
      Keyboard(wxWindow*, Progetto_pt2*);  

      void inputrel_evento();
      void creaposet_evento();
      void creacatena_evento();
      void minimali_evento();
      void massimali_evento();
      void copertura_evento();

  private:
      wxButton* inputrel;     //primo piano
      wxButton* creaposet;
      wxButton* creacatena;
      wxButton* minimali;
      wxButton* massimali;
      wxButton* copertura;

      wxSizer* box;
 
      Progetto_pt2* main;

      DECLARE_EVENT_TABLE()
};

#endif
