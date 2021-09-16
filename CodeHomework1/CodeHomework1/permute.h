/*Kushendra Ramrup
2/5/2020
CSCI 235
Professor Raja

@permute(const string & str) a function that calls the first and returns
all permutations of a string
@permute( const std::string &str, int low, int high) a function that goes through a string
making sure that it is not one letter, and uses the std::swap methd, recursion, and a for loop
to produce all possible permutations of the string.
*/
#pragma once
#include <iostream>
#include <cstdlib>
#include <string>

void permute( const std::string &str );
void permute( const std::string &str, int low, int high );

void permute( const std::string &str, int low, int high)
{
  std::string newstring = str;          //where one permute result will be stored
  if ( low == high ) {                  //makes sure it isn't one etter string
    for (int i = 0; i <= high; ++i)
      std::cout << newstring[i];        //prins out the permutation
    std::cout << std::endl;
  }
  else {
    for (int i=low; i<high; ++i) {     //as long as the string is more than 1 letter, go through letter by letter
      std::string tmp = newstring;     //where new sting permutation will be stored
      std::swap( newstring[i], newstring[low] );  //swapping letters to mae the permutation
      permute( newstring, low + 1, high );        //recursive call to continue the permute func
      std::swap( newstring[i], newstring[low] );
    }
  }
}

void permute( const std::string &str ) {
  int low = 0;
  int high = str.size();
  permute(str, low, high);
}

// void permute( const std::string & str, int low, int high ){
//   std::string s = str;
//   if (high == low) {std::cout << s << std::endl; return; }
//   else {
//     for (int i = low; i< high; i++) {
//       std::swap(s[low], s[i]);
//       permute(s, low+1, high);
//       std::swap(s, [low], s[i]);
//     }
//   }
// }
//
// void permute( const std::string & str ){
//   return permute(str, 0, str.length());
// }
