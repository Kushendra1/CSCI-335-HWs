//Kushendra Ramrup
//CSCI 335
//Professor Anita Raja
//Assignment 2: Question 1

//#include "dsexceptions.h"
//#include "avl_tree.h"
//#include <algorithm>
#include <iostream>
using namespace std;

/*
Implement the STL find routine that returns the iterator containing the first
occurrence of x in the range that begins at start and extends up to but not
including end. If x is not found, end is returned. This is a non-class (global
function) with signature:
template < typename Iterator, typename Object >
iterator find(Iterator start, Iterator end, const Object & x)
*/
template <typename Iterator, typename object>
Iterator my_find(Iterator start, Iterator end, const object & x) {
  for (; start != end; ++start){
    if (*start == x){
      return start;
    }
  }
  return end;
}
