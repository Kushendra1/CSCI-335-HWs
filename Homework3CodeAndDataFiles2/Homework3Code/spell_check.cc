/* Kushendra Ramrup
4/5/2020
Professor Raja
CSCI 335

Spell Check file
Spell checker made using a double hashing algorithm. I chose double hashing because during
testing the other parts I noiced it had the least amount of collisions. Also it was the most
recent one I worked with so it was easier to implement. This should output all of the correctly
spelled words, labeled as such, and all of the misspelled words. For each misspelled word
it should provide a list of candidate corrections from the dictionary. The three cases covered
are:
A) Adding one character in any possible position
B) Removing one character from the word
C) Swapping adjacent characters in the word
 */

#include "quadratic_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
using namespace std;

/*Helper function make_simple_word with one parameter that's a string not_simple
the helper function was made to simplified any words I may have to use the spell checker
on - that is that a simplified word is in all lower case letters, with all of the
characters in the string being just letters from the alphabet. It then returns not_simple
but now in a simplified form */
string make_simple_word(string not_simple) {
  int index = 0;
  for(char &c: not_simple) {
    if(c != 39 && c != 45 && ispunct(c)) {
      not_simple.erase(index, 1);
    }
    if(isalpha(c) && c >= 'A' && c <= 'Z') {
      c += 32;
    }
    index ++;
  }
  return not_simple;
}

/*Helper function first_caseA with one prameter that's a string wrong_word
the helper function was made to cover the first case in the spell check assignment -
adding one character in any possible position- and also to build a vector of possible
replacement words for the wrong_word. It goes through the inputed string, character by
character, and adds it to the vector in such a way that it allows for characters to be
added onto the end of it - thus creating the replacement. The vector candidates is then
returned. */
vector<string> first_caseA(string wrong_word) {
  vector<string> candidates;
  for (int i = 0; i <= wrong_word.length(); i++) {
    for (char c = 'a'; c <= 'z'; c++) {
      candidates.push_back(wrong_word.substr(0,i) + c + wrong_word.substr(i,wrong_word.length()));
    }
  }
  return candidates;
}

/*Helper function second_caseB with one parameter that's a string wrong_word
the helper function was made to cover the second case in the spell check assignment -
removing one character from the word- and also to build a vector of possible
replacement words for the wrong_word. This case creates temporary strings where
each letter, for the length of the original word, is erased and adds it to the
vector - thus creating the replacement. The vector candidates is returned. */
vector<string> second_caseB(string wrong_word) {
  vector<string> candidates;
  for (int i = 0; i < wrong_word.length(); i++) {
    string temp = wrong_word;
    candidates.push_back(temp.erase(i, 1));
  }
  return candidates;
}

/*Helper function third_caseC with one parameter that's a string wrong_word
the helper function was made to cover the third case in the spell check assignment -
swapping adjacent characters in the word- and also build a vector of possible
replacement words for the wrong_word. This case creates temporary strings where
each letter, for the length of he original word, is swapped with it's neighbor and
adds it to the vector - thus creating the replacement. The vector candidates is
returned */
vector<string> third_caseC(string wrong_word) {
  vector<string> candidates;
  for (int i = 0; i < wrong_word.length(); i++) {
    string temp = wrong_word;
    swap(temp[i], temp[i+1]);
    candidates.push_back(temp);
  }
  return candidates;
}

int testSpellingWrapper(int argument_count, char** argument_list) {

  const string document_filename(argument_list[1]);
  const string dictionary_filename(argument_list[2]);

  HashTableDouble<string> dictionary;
  dictionary.r_val(13);
  int collisions = 0;
  string dictionary_line;

  /*This block opens up an ifstream in order to read into the inputed text file
  and from that text file a hash table is made from its items. The hash table will
  be used later
  */
  ifstream fin(dictionary_filename.c_str());
  if (fin.fail()) {
    std::cerr << "File cannot be opened for reading." << std::endl;  //error message to be displayed if file can't be read/opened
    exit(1);
  }

  while (getline(fin, dictionary_line)) {
    dictionary.Insert(dictionary_line, collisions);
  }
  fin.close();
  // Call functions implementing the assignment requirements.

  
  string document_line, word;
  /*This block opens up an ifstream in order to read in a separate document text
  file. The items in this file are checked to see if they are in the hash table we
  created above. Befor it is checked, the word is simplified using the helper function.
  If the word is in the hash table, it is printed out along with the phrase is correct.
  If it is not found in the hash table it prints out the word along with the phrase
  is incorrect and then proceeds to call on all three of the helper functions for the three cases:
    a) Adding one character in any possible position
    b) Removing one character from the word
    c) Swapping adjacent characters in the word
  the replacement word and what case it falls under.
  */
  ifstream fin1(document_filename.c_str());
  if (fin1.fail()) {
    std::cerr << "File cannot be opened for reading." << std::endl;  //error message to be displayed if file can't be read/opened
    exit(1);
  }

  while(getline(fin1, document_line)) {
    stringstream ss(document_line);
    while(ss >> word) {
      string simplified_word =  make_simple_word(word);
      if(dictionary.Contains(simplified_word, collisions)) {
        std::cout << simplified_word << " is CORRECT" << std::endl;
      }
      else {
        std::cout << simplified_word << " is INCORRECT" << std::endl;
        for(auto candidate: first_caseA(simplified_word)) {
          if(dictionary.Contains(candidate, collisions)) {
            std::cout << "** " << simplified_word << " -> " << candidate << " ** case A" << std::endl;
          }
        }

        for(auto candidate: second_caseB(simplified_word)) {
          if(dictionary.Contains(candidate, collisions)) {
            std::cout << "** " << simplified_word << " -> " << candidate << " ** case B" << std::endl;
          }
        }

        for(auto candidate: third_caseC(simplified_word)) {
          if(dictionary.Contains(candidate, collisions)) {
            std::cout << "** " << simplified_word << " -> " << candidate << " ** case C" << std::endl;
          }
        }
      }
      }
    }
    fin1.close();
    return 0;
  }


// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE MAIN.
// WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE THERE.
// This main is only here for your own testing purposes.
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }

  testSpellingWrapper(argc, argv);

  return 0;
}
