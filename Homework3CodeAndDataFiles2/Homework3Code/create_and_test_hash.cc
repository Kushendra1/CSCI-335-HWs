/* Kushendra Ramrup
4/2/2020
Professor Raja
CSCI 335

Create and Test Hash File
This is where all of the probing happens. The TestFunctionForHashTable function is where
hash tables are created and queried, using either linear probing, quadratic probing, or
double hashing. The testFunctionWrapper function calls the previous function according
to what flag is indicated by the user in the terminal.*/
#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  hash_table.MakeEmpty();              // if for some reason the hash table has items, remove them

  /* This block opens up an ifstream in order to read into the inputed text file
  and from that text file a hash table is made from its items. While this is happening
  the amount of collisions is counted in the background and other numerical values can be
  found now that we have a hash table to work with. The required ones: amount of elements,
  table size, load factor, collisions, and average collisions are then printed out */
  int collisions = 0;
  string word_line;
  ifstream fin(words_filename.c_str());
  if (fin.fail()) {
    std::cerr << "File cannot be opened for reading." << std::endl;  //error message to be displayed if file can't be read/opened
    exit(1);
  }

  while (getline(fin, word_line)) {                //read in the text file and build a hash table using the items provided from it
    hash_table.Insert(word_line, collisions);
  }
  int item_count = hash_table.get_items();        //get the current item count and table size using the accessor funcs
  int table_size = hash_table.get_Size();
  fin.close();

  double load_factor = (double)item_count/table_size;        //calculating load factor and average number of collisions with the info I got from the accessors above
  double avg_collisions = (double)collisions/item_count;

  cout << "number_of_elements: " << item_count << endl;     //printing out the required values as specified in the pdf and not as how they print statements
  cout << "size_of_table: " << table_size << endl;          //were intially given. That format is item name and then the numerical value
  cout << "load_factor: " << load_factor << endl;
  cout << "collisions: " << collisions << endl;
  cout << "avg_collisions: "<< avg_collisions << endl;
  cout << endl;

  /* This block opens up a second ifstream in order to read into the inputed query
  text file. The items in this file are checked t see if they are in the hash table we
  created above. Probes are counted here by passing through the collisions parameter,
  since collisions and prbes occur in the same place - with the difference being probes are
  reset. Then it is printed out whether or not the item is found in the hash table and how
  many probes it took to do so. */
  ifstream fin1(query_filename.c_str());
  if (fin1.fail()) {
    std::cerr << "File cannot be opened for reading." << std::endl;  //error message to be displayed if file can't be read/opened
    exit(1);
  }

  string query_line;
  while (getline(fin1, query_line)) {           //read in the text file to see it its items are in the newly made hash table
    int probes = 1;
    if (hash_table.Contains(query_line, probes)) {
      cout<< query_line << " Found " << probes << endl;      //indicate whether or not the item is found in the hash table
    }
    else {
      cout<< query_line << " Not_Found " << probes << endl;
    }
  }
  collisions = 0;                              //reset collisions to zero for next call
  fin1.close();
}

int testFunctionWrapper(int argument_count, char **argument_list) {
  const string words_filename(argument_list[1]);
  const string query_filename(argument_list[2]);
  const string param_flag(argument_list[3]);

  /* This block of if statements calls the specific type of hashing the user
  wants as indicated by the flag they provide in the terminal. It first creates
  a hash table and then calls the TestFunctionForHashTable function to use either
  linear, quadratic, or double probing. For double hashing a fourth argumnt list had
  to be created and kept in the if statement as the other three calls are not expecting
  the fourth agument list */
  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    const string R_flag(argument_list[4]);
    double_probing_table.r_val(stoi(R_flag));
    std::cout << "r_value: " << stoi(R_flag) << std::endl;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
  } else {
    cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE MAIN.
// WE WILL DIRECTLY CALL testFunctionWrapper. ALL FUNCTIONALITY SHOULD BE THERE.
// This main is only here for your own testing purposes.
int main(int argc, char **argv) {

  /*if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
    }*/

  testFunctionWrapper(argc, argv);
  return 0;
}
