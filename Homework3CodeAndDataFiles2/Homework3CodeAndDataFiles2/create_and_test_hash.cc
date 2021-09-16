// YOUR NAME.

#include "quadratic_probing.h"
#include "linear_probing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();
  //..Insert your own code

  int collisions = 0;
  string word_line;

  std::ifstream fin(words_filename.c_str());
  if (fin.fail()) {
    std::cerr << "File cannot be opened for reading." << std::endl;  //error message to be displayed if file can't be read/opened
    exit(1);
  }

  while (getline(fin, word_line)) {
    hash_table.Insert(word_line, collisions);
  }
  int item_count = hash_table.get_items();
  int table_size = hash_table.Size();

  fin.close();

  double load_factor = (double)item_count/table_size;
  double avg_collisions = (double)collisions/item_count;

  cout << "number_of_elements: " << item_count << endl;
  cout << "size_of_table: " << table_size << endl;
  cout << "load_factor: " << load_factor << endl;
  cout << "collisions: " << collisions << endl;
  cout << "avg_collisions: "<< avg_collisions << endl;
  cout << endl;

  std::ifstream fin1(query_filename.c_str());
  if (fin.fail()) {
    std::cerr << "File cannot be opened for reading." << std::endl;  //error message to be displayed if file can't be read/opened
    exit(1);
  }

  string query_line;
  while (getline(fin1, query_line)) {
    int probes = 1;
    if (hash_table.Contains(query_line, probes)) {
      cout<< query_line << " Found " << probes << endl;
    }
    else {
      cout<< query_line << " Not_Found " << probes << endl;
    }
  }
  collisions = 0;
  fin1.close();
}

int testFunctionWrapper(int argument_count, char **argument_list) {
  const string words_filename(argument_list[1]);
  const string query_filename(argument_list[2]);
  const string param_flag(argument_list[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
  } else if (param_flag == "double") {
    // HashTableDouble<string> double_probing_table;
    // TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
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

  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }

  testFunctionWrapper(argc, argv);
  return 0;
}
