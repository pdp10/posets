#include "Menu.h"
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
#include <fstream>
using namespace std;


enum  { PULISCI = 1,
        APRI,   //file
	SALVA, 
	ESCI, 
	COPIA,     //modifica
	INCOLLA,
	TOP,        //funzionalita'
	BOTTOM, 
	RFLX_CLSR, 
	TRNS_CLSR, 
	CATENA_N, 
	SUCCESSORI, 
	PREDECESSORI, 
	INVERSA,
	MINIMALI_INS,
	MASSIMALI_INS,
	LIVELLO,
	AIUTO,       //aiuto
	INFO };


Menu::Menu(Progetto_pt2* app, const wxString& titolo, const wxPoint& pos, const wxSize& size, long style)
                             : wxFrame(NULL, -1, titolo, pos, size, style), main(app)  {

    //create a menu 
    wxMenu *file = new wxMenu;
    wxMenu *modifica = new wxMenu;
    wxMenu *funzioni = new wxMenu;
    wxMenu *aiuto = new wxMenu;

    //Inserisce le funzionalita'

    file->Append(PULISCI,  _T("&Pulisci\tAlt-P"),     _T("Pulisce tutte le righe di testo"));
    file->Append(APRI,  _T("&Apri\tAlt-A"),     _T("Apre una relazione salvata"));
    file->Append(SALVA, _T("&Salva\tAlt-S"),    _T("Salva la relazione in un file"));
    file->Append(ESCI,  _T("&Esci\tAlt-E"),     _T("Uscita dal programma"));

    modifica->Append(COPIA,   _T("Co&pia\tAlt-C"),   _T("Copia la relazione di input"));
    modifica->Append(INCOLLA, _T("Inco&lla\tAlt-L"), _T("Incolla la relazione di input"));

    funzioni->Append(TOP,          _T("&Top\tAlt-T"),                        _T("Visualizza il top della catena"));
    funzioni->Append(BOTTOM,       _T("&Bottom\tAlt-B"),                     _T("Visualizza il bottom della catena"));
    funzioni->Append(RFLX_CLSR,    _T("Chiusura &Riflessiva\tAlt-R"),        _T("Chiusura riflessiva della relazione"));
    funzioni->Append(TRNS_CLSR,    _T("Chiusura Tra&nsitiva\tAlt-N"),        _T("Chiusura transitiva della relazione"));
    funzioni->Append(CATENA_N,     _T("Catena Ennesi&ma\tAlt-M"),            _T("Crea una catena di n elementi"));
    funzioni->Append(SUCCESSORI,   _T("S&uccessori\tAlt-U"),                 _T("Trova i successori di un sottoinsieme"));
    funzioni->Append(PREDECESSORI, _T("Pre&decessori\tAlt-D"),               _T("Trova i predecessori di un sottoinsieme"));
    funzioni->Append(INVERSA,      _T("In&versa\tAlt-V"),                    _T("Trova la relazione inversa"));
    funzioni->Append(MINIMALI_INS, _T("M&inimali del sottoinsieme\tAlt-I"),  _T("Trova i minimali del sottoinsieme"));
    funzioni->Append(MASSIMALI_INS,_T("Ma&ssimali del sottoinsieme\tAlt-S"), _T("Trova i massimali del sottoinsieme"));
    funzioni->Append(LIVELLO,      _T("&Livello\tAlt-L"),                    _T("Trova gli elementi del livello specificato"));

    aiuto->Append(AIUTO, _T("Aiut&o..\tAlt-O"),       _T("Aiuto sulla sintassi corretta"));
    aiuto->Append(INFO,  _T("&Informazioni..\tAlt-I"), _T("Informazioni generali sul progetto"));

    // appende i menu creati nel menubar
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(file,     _T("&File"));
    menuBar->Append(modifica, _T("Mo&difica"));
    menuBar->Append(funzioni, _T("Fun&zioni"));
    menuBar->Append(aiuto,    _T("Ai&uto"));

    SetMenuBar(menuBar);

    CreateStatusBar(3);  //Nel secondo spazio saranno inseriti i commenti..
}

//Funzioni di File

void Menu::OnLogClear(wxCommandEvent& WXUNUSED(event)) {  main->clean_all(); }

void Menu::OnOpen(wxCommandEvent& WXUNUSED(event)) {
    ifstream bk_p("backup_progetto",ios::in);
    if(!bk_p)  {  main->set_log_status("File backup_progetto inesistente"); return; } 
    char cc = bk_p.get();
    string inp1, inp2, out1, out2;
    int newline = 0;
    while(!bk_p.eof()){
	cc = bk_p.get();
        switch(newline) {
           case 4: cc = bk_p.get();  while(cc != '\n') { inp1.push_back(cc); cc = bk_p.get(); }  break;
           case 6: cc = bk_p.get();  while(cc != '\n') { inp2.push_back(cc); cc = bk_p.get(); }  break;
           case 8: cc = bk_p.get();  while(cc != '\n') { out1.push_back(cc); cc = bk_p.get(); }  break;
           case 10: cc = bk_p.get(); while(cc != '\n') { out2.push_back(cc); cc = bk_p.get(); }  break;
	}
	if(cc == '\n') newline++;
    }
    main->set_open_file(inp1, inp2, out1, out2);
    main->set_log_status("File backup_progetto aperto correttamente");  
}

void Menu::OnSave(wxCommandEvent& WXUNUSED(event)) { 
    ofstream bk_p("backup_progetto",ios::out);
    if(!bk_p)  {  main->set_log_status("Impossibile salvare la relazione"); return; } 
    string inp1, inp2, out1, out2;
    inp1 = main->get_string();
    inp2 = main->get_string_I();
    out1 = main->get_string_out1();
    out2 = main->get_string_out2();
    for(int i = 0; i < 5; i++) {
      switch(i) {
         case 0: bk_p << "# File di back up dei controlli: non modificare "
		         "questo file se non si conosce la sintassi. Per informazioni consultare Aiuto/Help\n\n\n";            break;
         case 1: bk_p << "Input della Relazione:\n\t"                 << inp1 << endl;  break;
         case 2: bk_p << "Input dell'Insieme:\n\t"                    << inp2 << endl;  break;
	 case 3: bk_p << "Output di Relazione, Poset, Catena:\n\t"    << out1 << endl;  break;
	 case 4: bk_p << "Output del Dominio o di altri Insiemi:\n\t" << out2 << endl;  break;
      }
    }
    main->set_log_status("Relazione salvata in backup_progetto");
}

void Menu::OnQuit(wxCommandEvent& WXUNUSED(event)){ Close(TRUE); }



//Funzioni di Modifica
void Menu::OnCopy(wxCommandEvent& WXUNUSED(event)) {
    cp_pst = main->get_string();
    if(cp_pst.size() == 0)          
        main->set_log_status("Attenzione: copia di stringa vuota");
}

void Menu::OnPaste(wxCommandEvent& WXUNUSED(event)) {
  if(cp_pst.size() == 0) 
       main->set_log_status("Attenzione: incolla di stringa vuota");
  main->paste_string(cp_pst.c_str());
}



//Funzioni di Funzioni 
void Menu::top_evento(wxCommandEvent& WXUNUSED(event)) {
   Relazione* rel = main->current();
   if(rel) {
      Catena* cat = dynamic_cast<Catena*>(rel);
      if(cat) {
          Insieme<char>* sing = new Insieme<char>;
          sing->add(cat->top());
          main->set_value(sing);
      }
      else {
          string str("Top non e' un metodo di ");
          str += rel->get_nome(); 
          main->set_log_status(str);
      }
   }
   else main->set_current(rel);      //caso di errore
}


void Menu::bottom_evento(wxCommandEvent& WXUNUSED(event)) {
   Relazione* rel = main->current();
   if(rel) {
      Catena* cat = dynamic_cast<Catena*>(rel);
      if(cat) {
          Insieme<char>* sing = new Insieme<char>;
          sing->add(cat->bottom());
          main->set_value(sing);
      }
      else  {
          string str("Bottom non e' un metodo di ");
          str += rel->get_nome(); 
          main->set_log_status(str);
      }
   }
   else main->set_current(rel);  // caso di errore
}

void Menu::reflex_closure_evento(wxCommandEvent& WXUNUSED(event)) {  // vedere
      string str = main->get_string();
      Temp t;
      Relazione* rel = 0;
      if(t.parsing(str)) {
           Insieme<Coppia<char> > R = t.create_str(str);
           rel = new Relazione(R);
	   rel->reflex_closure();
      }
      main->set_current(rel);       
}

void Menu::trans_closure_evento(wxCommandEvent& WXUNUSED(event)) { 
      string str = main->get_string();
      Temp t;
      Relazione* rel = 0;
      if(t.parsing(str)) {
           Insieme<Coppia<char> > R = t.create_str(str);
           rel = new Relazione(R);
	   rel->trans_closure();
      }
      main->set_current(rel);
}

void Menu::catena_n_evento(wxCommandEvent& WXUNUSED(event)) { 
      string str = main->get_string_I();
      Temp t;
      Catena* cat_n = 0;
      if(t.parsing_single(str)) {
	  cat_n = new Catena(t.create_single(str));    // richiama il costruttore Catena(const int&);
	  main->set_current(cat_n);
	  main->set_log_status("Catena costruita sui caratteri ASCII");

      }
      else   main->set_value(0);
}


void Menu::successori_evento(wxCommandEvent& WXUNUSED(event)) {     
     Relazione* rel = main->current();
     if(rel) {
         string str = main->get_string_I();
         Temp t;
         Insieme<char>* I = 0, *succ = 0; 
         if(t.parsing_I(str)) {
              I = new Insieme<char>(t.create_I_str(str));
              succ = new Insieme<char>(rel->post2(*I));
	 }
         main->set_value(succ);
     }
     else main->set_current(rel);   //caso di errore
}

void Menu::predecessori_evento(wxCommandEvent& WXUNUSED(event)) {
     Relazione* rel = main->current();
     if(rel) {
         string str = main->get_string_I();
         Temp t;
         Insieme<char>* I = 0, *pred = 0; 
         if(t.parsing_I(str)) {
              I = new Insieme<char>(t.create_I_str(str));
              pred = new Insieme<char>(rel->pred2(*I));
	 }
	 main->set_value(pred);
     }
     else main->set_current(rel);   //caso di errore
}

void Menu::inversa_evento(wxCommandEvent& WXUNUSED(event)) {
     Relazione* rel = main->current();
     if(rel)   rel = new Relazione(rel->inversa());
     main->set_current(rel);
}



void Menu::minimali_ins_evento(wxCommandEvent& WXUNUSED(event)) {
     Relazione* rel = main->current();
     if(rel) {
         string str = main->get_string_I();
         Temp t;
         Insieme<char>* I = 0, *min = 0; 
	 Poset* pos = dynamic_cast<Poset*>(rel);
         if(pos && t.parsing_I(str)) { 
	     I = new Insieme<char>(t.create_I_str(str));
             min = new Insieme<char>(pos->minimali(*I));
	 }
         main->set_value(min);
	 if(!pos) main->set_log_status("Minimali non e' implementato in Relazione");
     }
     else main->set_current(rel);
}

void Menu::massimali_ins_evento(wxCommandEvent& WXUNUSED(event)) {
     Relazione* rel = main->current();
     if(rel) {
         string str = main->get_string_I();
         Temp t;
         Insieme<char>* I = 0, *max = 0; 
	 Poset* pos = dynamic_cast<Poset*>(rel);
         if(pos && t.parsing_I(str)) { 
	     I = new Insieme<char>(t.create_I_str(str));
             max = new Insieme<char>(pos->massimali(*I));
	 }
         main->set_value(max);
	 if(!pos) main->set_log_status("Massimali non e' implementato in Relazione");
     }
     else main->set_current(rel);
}

void Menu::livello_evento(wxCommandEvent& WXUNUSED(event)) { 
     Relazione* rel = main->current();
     if(rel) {
         string str = main->get_string_I();
         Temp t;
         int i = 0;
         Insieme<char>* I = 0;
	 Poset* pos = dynamic_cast<Poset*>(rel);
         if(pos && t.parsing_single(str)) {
              i = t.create_single(str);
	      I = new Insieme<char>(pos->livello(i));
	 }
	 main->set_value(I);
	 if(!pos) main->set_log_status("Livello non e' implementato in Relazione");
     }
     else main->set_current(rel);  //caso di errore
}




//Funzione di Aiuto
void Menu::OnHelp(wxCommandEvent& WXUNUSED(event)) {
    wxMessageDialog dialog(this,
                           _T("Quest'applicazione consente di studiare una Relazione, un Poset o una Catena mediante\n")
                           _T("due righe di input. La prima e' la riga delle relazioni, la seconda degli insiemi.\n")
                           _T("Entrambe sono caratterizzate da una particolare sintassi:\n")
			   _T("\n")
                           _T("Input della relazione:\n")
                           _T("    {(char,char),(char,char),...,(char,char)}\n")
                           _T("\n")
                           _T("Input dell'insieme\n")
                           _T("    {char,char,...,char}\n")
                           _T("\n")
			   _T("NB per Poset o Catena. Se si vogliono ottenere gli elementi di un particolare livello,\n") 
			   _T("l'input dell'insieme deve avere questa sintassi:\n")
			   _T("\n")
			   _T("    {abc..z} dove abc..z sono char numerici compresi tra 0 e 9.\n")
			   _T("\n") 
			   _T("E' possibile inoltre salvare in un opportuno file chiamato backup_progetto le quattro\n")
                           _T("righe di testo tramite la funzione Salva, e recuperare le medesime righe con la funzione \n")
                           _T("Apri. Il file backup_progetto puo' essere modificato, ma si deve fare attenzione a non \n")
                           _T("alterarne gli spazi e i newline.\n")
			   _T("Le funzioni Copia e Incolla permettono di memorizzare la relazione di input (Copia) e di\n")
			   _T("ripristinare la medesima relazione in un momento successivo (Incolla), sempre nella riga\n")
			   _T("dell'input della relazione"),
                           _T("Aiuto sulla sintassi corretta.."));

    dialog.ShowModal();
}



void Menu::OnAbout(wxCommandEvent& WXUNUSED(event)) {
    wxString msg, info("Progetto di Programmazione 2 - Anno Accademico 2003/2004\n\n"
		       "Piero Dalle Pezze - Matricola 486228\n");
    msg.Printf( _T(info), wxVERSION_STRING);
    wxMessageBox(msg, _T("Informazioni Generali"), wxOK | wxICON_INFORMATION, this);
}


BEGIN_EVENT_TABLE(Menu,  wxFrame)
      EVT_MENU(PULISCI,        Menu::OnLogClear)
      EVT_MENU(APRI,           Menu::OnOpen)
      EVT_MENU(SALVA,          Menu::OnSave)
      EVT_MENU(ESCI,           Menu::OnQuit)
      EVT_MENU(COPIA,          Menu::OnCopy)
      EVT_MENU(INCOLLA,        Menu::OnPaste)
      EVT_MENU(TOP,            Menu::top_evento)
      EVT_MENU(BOTTOM,         Menu::bottom_evento)
      EVT_MENU(RFLX_CLSR,      Menu::reflex_closure_evento)
      EVT_MENU(TRNS_CLSR,      Menu::trans_closure_evento)
      EVT_MENU(CATENA_N,       Menu::catena_n_evento)
      EVT_MENU(SUCCESSORI,     Menu::successori_evento)
      EVT_MENU(PREDECESSORI,   Menu::predecessori_evento)
      EVT_MENU(INVERSA,        Menu::inversa_evento)
      EVT_MENU(MINIMALI_INS,   Menu::minimali_ins_evento)
      EVT_MENU(MASSIMALI_INS,  Menu::massimali_ins_evento)
      EVT_MENU(LIVELLO,        Menu::livello_evento)
      EVT_MENU(AIUTO,          Menu::OnHelp)
      EVT_MENU(INFO,           Menu::OnAbout)
END_EVENT_TABLE()
