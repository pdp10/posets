#ifndef COPPIA_H
#define COPPIA_H

#include<iostream>
using std::ostream;

class Coppia {
 public:
  Coppia();
  Coppia(const int&,const int&);
  int read1() const;
  int read2() const;
  bool operator==(const Coppia&) const;
  bool operator!=(const Coppia&) const;
  friend ostream& operator<<(ostream&, const Coppia&);
 private:
  int uno;
  int due;
};

#endif

