#include <iostream>
#include <cstdlib>
#include "permute.h"

void permute( const string & str, int low, int high ){
  string s = str;
  if (high == low) {cout << s << endl; return; }
  else {
    for (int i = low; i< high; i++) {
      swap(s[low], s[i]);
      permute(s, low+1, high);
      swap(s, [low], s[i]);
    }
  }
}

void permute( const string & str ){
  return permute(str, 0, str.length());
}
