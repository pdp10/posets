#ifndef COPPIA_H
#define COPPIA_H

#include<string>
#include<iostream>
using namespace std;

template<class T>
class Coppia {
 public:
  Coppia();
  Coppia(const T&,const T&);
  T read1() const;
  T read2() const;
  const char* write() const;
  bool operator==(const Coppia&) const;
  bool operator!=(const Coppia&) const;
  friend ostream& operator<< <T>(ostream&, const Coppia<T>&);
 private:
  T uno;
  T due;
};


//COSTRUTTORI

template<class T>
Coppia<T>::Coppia(): uno('0'), due('0') {} 

template<class T>
Coppia<T>::Coppia(const T& _uno, const T& _due): uno(_uno), due(_due) {}

//OPERATORI

template<class T>
bool Coppia<T>::operator==(const Coppia& _Coppia) const {
  return read1() == _Coppia.read1() && read2() == _Coppia.read2(); } 

template<class T>
bool Coppia<T>::operator!=(const Coppia& _Coppia) const {
  return read1() != _Coppia.read1() || read2() != _Coppia.read2(); }

template<class T>
ostream& operator<<(ostream& os, const Coppia<T>& _Coppia) {
  return os << '(' << _Coppia.read1() << ',' << _Coppia.read2() <<')';
}

template<class T>
const char* Coppia<T>::write() const {
  string str;
  str.push_back('(');
  str.push_back(read1());
  str.push_back(',');
  str.push_back(read2());
  str.push_back(')');
  return str.c_str();
}

template<class T>
T Coppia<T>::read1() const { return uno; }

template<class T>
T Coppia<T>::read2() const { return due; }

#endif

