#include"Coppia.h"
#include<iostream>
using namespace std;

//COSTRUTTORI
Coppia::Coppia(): uno(0), due(0) {}
Coppia::Coppia(const int& _uno, const int& _due): uno(_uno), due(_due) {}

//OPERATORI
bool Coppia::operator==(const Coppia& _Coppia) const {
  return uno == _Coppia.uno && due == _Coppia.due; } 
bool Coppia::operator!=(const Coppia& _Coppia) const {
  return uno != _Coppia.uno || due != _Coppia.due; }

ostream& operator<<(ostream& os, const Coppia& _Coppia) {
  return os << '(' << _Coppia.uno << ',' << _Coppia.due <<')';
}

int Coppia::read1() const { return uno; }
int Coppia::read2() const { return due; }

