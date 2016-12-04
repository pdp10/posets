#ifndef MENU_H
#define MENU_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
   #include "wx/wx.h"
   #include "wx/menu.h"
#endif



class Progetto_pt2;

class Menu: public wxFrame {
  public:
  Menu(Progetto_pt2*, const wxString&, const wxPoint&, const wxSize&, long = wxDEFAULT_FRAME_STYLE);

      void OnLogClear(wxCommandEvent&);    //file
      void OnOpen(wxCommandEvent&);   
      void OnSave(wxCommandEvent&);
      void OnQuit(wxCommandEvent&);

      void OnCopy(wxCommandEvent&);  //modifica
      void OnPaste(wxCommandEvent&);

      void top_evento(wxCommandEvent&);     //funzionalita'
      void bottom_evento(wxCommandEvent&);
      void reflex_closure_evento(wxCommandEvent&);
      void trans_closure_evento(wxCommandEvent&);
      void catena_n_evento(wxCommandEvent&);
      void successori_evento(wxCommandEvent&);
      void predecessori_evento(wxCommandEvent&);
      void inversa_evento(wxCommandEvent&);
      void minimali_ins_evento(wxCommandEvent&);
      void massimali_ins_evento(wxCommandEvent&);
      void livello_evento(wxCommandEvent&);

      void OnHelp(wxCommandEvent&);   //aiuto e altro
      void OnAbout(wxCommandEvent&);    


  private:
      DECLARE_EVENT_TABLE()
      Progetto_pt2* main;
      wxString cp_pst;   //stringa per il copia incolla
};

#endif
