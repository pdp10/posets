#ifndef RELAZIONE_H
#define RELAZIONE_H

#include"Coppia.h"
#include"Insieme.h"
#include<iostream>
#include<string>
using namespace std;


class Relazione {
  private:
    static string nome;
  protected:
    Insieme<char> I;
    Insieme<Coppia<char> > R;
  public:
    friend ostream& operator<<(ostream&, const Relazione&);
    Relazione();
    Relazione(const Insieme<Coppia<char> >&);
    Relazione(const Insieme<char>&, const Insieme<Coppia<char> >&); 
    virtual bool add(const char&, const char&);
    bool remove(const char&, const char&);
    Relazione operator*(const Relazione&);
    Relazione inversa();
    bool operator()(const char&, const char&);
    bool total() const;
    void trans_closure();
    void reflex_closure();
    void remove_trans_closure();    //per la copertura..per ottenere la coppie base 
    void remove_reflex_closure();
    Insieme<char> post(const char&) const;
    Insieme<char> post_(const char&) const;                  //successori propri
    Insieme<char> post2(const Insieme<char>&) const;  //successori per insieme
    Insieme<char> post2_(const Insieme<char>&) const; //successori propri per insieme
    Insieme<char> pred(const char&) const;   
    Insieme<char> pred_(const char&) const;                  //predecessori propri
    Insieme<char> pred2(const Insieme<char>&) const;  //predecessori per insieme
    Insieme<char> pred2_(const Insieme<char>&) const; //predecessori propri per insieme
    bool acyclic();
    Insieme<char> getIns() const;
    Insieme<Coppia<char> > getInsCop() const;
    virtual string get_nome() const;
    virtual ~Relazione();
};



#endif
