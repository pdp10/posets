#include "Temp.h"
#include <iostream>
#include "Insieme.h"
#include "Coppia.h"
#include "Relazione.h"
#include "Poset.h"
#include "Catena.h"
#include <string>
using namespace std;

Temp::Temp() {}

Insieme<Coppia<char> > Temp::create_str(const string& str) {
    unsigned int i = 1;   
    char p1, p2;
    Insieme<Coppia<char> > R;
    while(i < str.size()-1) {
        if(str[i-1] == '(') p1 = str[i];
        if(str[i+1] == ')') {
           p2 = str[i];
	   R.add(Coppia<char>(p1, p2));
        }
        i++;
    }
    return R;
}


Insieme<char> Temp::create_I_str(const string& str) {
    unsigned int i = 1;   
    Insieme<char> I;
    while(i < str.size()-1) { 
       if(i%2 == 1)        //i pari sono ',' o graffe
	   I.add(str[i]);
       i++;
    }
    return I;
}



int Temp::somma(int* A, int pos) {
     int num = 0;
     for(int i=0; i<pos; i++){
        int j = pos-i-1, dec=1;   // cifre
        while(j > 0){
            dec *= 10;            // calcolo di n*(10^?)
            j--;
        }
	num += (A[i]*dec);   // es. 100  ==>> 130 ==>> 132
     }
     return num;
}

void Temp::calcola(int *A, char c, int& pos) {
     int i = c - '0';
     A[pos] = i;           //es. 132 ==>> A[0]=1, A[1]=3, A[2]=2
     pos++;
}

int Temp::create_single(const string& str){
     int* A = new int[str.size()-1](0);          // primo & ultimo elem sono graffe
     int i=1, num=0, pos=0;                       //array dove memorizzare le cifre
     while(str[i] != '}') {
	  calcola(A, str[i], pos);              // inserimento della cifra letta
	  i++;
     } 
     num = somma(A,pos);
     delete []A;
     return num;
}


bool Temp::parsing(const string& str) {  // {(2,3),(6,7),(1,2)}
     unsigned int i = 1, stato = 1;
     bool parsing = false;
     if(str[0] == '{') parsing = true;  
     while(i < str.size()-1 && parsing) {  
        switch(str[i]) {
            case '(':  if(stato==1){ stato++; i++; } 
                       else parsing = false; break; 
            case ',':  if(stato==3){ stato++; i++; break; } 
	               if(stato==6){ stato = 1; i++; break; }  
                       else parsing = false; break;
            case ')':  if(stato==5){ stato++; i++; }
                       else parsing = false; break;
            default:   if(stato == 2 || stato == 4) { stato++; i++;}
                       else parsing = false;
	}
     }
     if(parsing && (str[i] != '}' || (stato != 6 && stato != 1))) parsing = false;  //accetta {}
     return parsing;
}

bool Temp::parsing_I(const string& str) {  // {2,3,6,7,1,2}
     unsigned int i = 1;
     bool parsing = false;
     if(str[0] == '{') parsing = true;  
     while(i < str.size()-1 && parsing) {  
        switch(str[i]) {
            case ',':  i++; break;  
   	    default:   if(i%2) i++; //, ha sempre stato pari
                       else parsing = false; 
	}
     }
     if(str[i] != '}') parsing = false;  //accetta {}
     return parsing;
}

bool Temp::parsing_single(const string& str) {  // es. {2}
     unsigned int i = 1;
     bool parsing = false;
     if(str.size() >= 3 && str[0] == '{') parsing = true;   //affinche' nn si tratti di str vuota
     while(i < str.size()-1 && parsing) {
         if(str[i]<'0' || str[i]>'9') parsing = false;
         i++;
     }
     if(str[i] != '}') parsing = false; 
     return parsing;
}
