#include "Progetto_pt2.h"
#include<iostream>
using namespace std;

IMPLEMENT_APP(Progetto_pt2)

bool Progetto_pt2::OnInit() {
      frame = new Menu(this, "Progetto di Programmazione 2 - Relazioni, Poset, Catene",  //Menu e' derivata da wxFrame !!
		       wxPoint(100,150), wxSize(775,470), wxDEFAULT_FRAME_STYLE);  //Crea frame


      SetTopWindow(frame);          //visualizza frame

      wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);  //celle del frame


      keyb = new Keyboard(frame, this);       
      st1 = new wxStaticText(frame,-1,"\nInserire la relazione:");  //wxStaticText
      input = new wxTextCtrl(frame, -1, _T(""), wxPoint(5,260), wxSize(300,75), wxTE_MULTILINE);            //input_rel
      st2 = new wxStaticText(frame,-1,"Inserire l'insieme:");
      input_fun = new wxTextCtrl(frame, -1);        //per insiemi
      st3 = new wxStaticText(frame,-1,"\n\nOutput delle relazioni, dei poset e delle catene:");               //spazio
      output = new wxTextCtrl( frame, -1, _T(""), wxPoint(5,260), wxSize(300,100), wxTE_MULTILINE | wxTE_READONLY);   
      st4 = new wxStaticText(frame,-1,"Output del dominio e degli insiemi:");
      output_fun = new wxTextCtrl(frame, -1, _T(""), wxPoint(5,260), wxSize(300,50), wxTE_MULTILINE | wxTE_READONLY);  


      vbox->Add(keyb,       0);                
      vbox->Add(st1,        0);
      vbox->Add(input,      0, wxGROW);
      vbox->Add(st2,        0);
      vbox->Add(input_fun,  0, wxGROW);
      vbox->Add(st3,        0);
      vbox->Add(output,     0, wxGROW);
      vbox->Add(st4,        0);
      vbox->Add(output_fun, 0, wxGROW);

      frame->SetSizer(vbox);     

      stato = string("Relazione corrente:");

      frame->SetStatusText(stato.c_str(), 2);   //inserisce nel secondo spazio della StatusBar   

      cur = 0;
      i_cur = 0;

      frame->Show(true);

      return true;
}


const char* Progetto_pt2::get_string() {
      wxString str;
      str = input->GetValue();
      return str.c_str();
}

const char* Progetto_pt2::get_string_I() {
      wxString str;
      str = input_fun->GetValue();
      return str.c_str();
}

const char* Progetto_pt2::get_string_out1() {
      wxString str;
      str = output->GetValue();
      return str.c_str();
}

const char* Progetto_pt2::get_string_out2() {
      wxString str;
      str = output_fun->GetValue();
      return str.c_str();
}


Relazione* Progetto_pt2::current() {  return cur; }
Insieme<char>* Progetto_pt2::i_current() {  return i_cur; }

void Progetto_pt2::set_current(Relazione* pos) { //Polimorfo
      if(cur) delete cur;
      cur = pos;
      output->Clear();
      output_fun->Clear();
      if(cur) {
	    string rel_name(cur->get_nome());
            stato = "Relazione corrente: " + rel_name; //modifica della relaz.corrente
            frame->SetStatusText(stato.c_str(), 2);  
            output_fun->WriteText("Dominio ");
	    output_fun->WriteText(rel_name.c_str());
	    output_fun->WriteText(": ");
            if(dynamic_cast<Poset*>(pos))   output->WriteText("Relazione d'ordine: ");
            else                            output->WriteText("Relazione: ");
            output_fun->WriteText(cur->getIns().write_I());  
            output->WriteText(cur->getInsCop().write());              
      }
      else {
            frame->SetStatusText("Relazione corrente: Errore", 2);
            msg_error();
      }
}

void Progetto_pt2::set_value(Insieme<char>* I) {
      if(i_cur) delete i_cur;
      i_cur = I;
      output_fun->Clear();
      if(i_cur) {
            output_fun->WriteText("Insieme: ");
            output_fun->WriteText(i_cur->write_I());
      }
      else  msg_error_I();
}

void Progetto_pt2::set_open_file(string inp1, string inp2, string out1, string out2) {
  input->Clear();
  input_fun->Clear();
  output->Clear();
  output_fun->Clear();
  input->WriteText(inp1.c_str());
  input_fun->WriteText(inp2.c_str());
  output->WriteText(out1.c_str());
  output_fun->WriteText(out2.c_str());
}

void Progetto_pt2::paste_string(string str) { input->Clear(); input->WriteText(str.c_str()); }

void Progetto_pt2::set_log_status(string str) {  frame->SetStatusText(str.c_str(), 1); }

void Progetto_pt2::clean_all() {
    input->Clear();
    input_fun->Clear();
    output->Clear();
    output_fun->Clear();
    cur = 0;
    i_cur = 0;
    frame->SetStatusText("", 1);
    frame->SetStatusText("Relazione corrente: ", 2);
}

void Progetto_pt2::msg_error() { 
    wxString msg, err("ATTENZIONE: L'input della relazione \ncontiene un errore di sintassi oppure e' vuoto");
    msg.Printf( _T(err), wxVERSION_STRING);
    wxMessageBox(msg, _T("Errore nell'input della relazione"), wxOK | wxICON_EXCLAMATION, frame);
}

void Progetto_pt2::msg_error_I() { 
    wxString msg, err("ATTENZIONE: L'input dell'insieme \ncontiene un errore di sintassi oppure e' vuoto");
    msg.Printf( _T(err), wxVERSION_STRING);
    wxMessageBox(msg, _T("Errore nell'input dell'insieme"), wxOK | wxICON_EXCLAMATION, frame);
}
