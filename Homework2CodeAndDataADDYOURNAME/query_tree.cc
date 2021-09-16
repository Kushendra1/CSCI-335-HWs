//Kushendra Ramrup
//CSCI 335
//Professor Anita Raja
//Assignment 2: Question 2 part A

/* A parser to read in this database and construct an AVL tree. For each line of
the database and for each recognition sequence in that line, it creates a new
SequenceMap object that contains the recognition sequence as its recognition_sequence_
and the enzyme acronym as the only string of its enzyme_acronyms_, and inserts
this object into the tree.
*/

#include "avl_tree_p2a.h"
#include "sequence_map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

namespace {
#include <iostream>
  //void build_tree

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  // Code for running Part2(a)
  // You can use public functions of TreeType. For example:
  //a_tree.insert(10);
  //a_tree.printTree();

  std::ifstream fin(db_filename.c_str());
  if (fin.fail()) {
    std::cerr << "File cannot be opened for reading." << std::endl;  //error message to be displayed if file can't be read/opened
    exit(1);
  }

  //AvlTree<SequenceMap> a_tree;
  /* takes in the fstream of the input file, and then breaks it down further
  with a stringstream in order to get parts of the line. The parts are stored
  s that we get the enzyme acronym from each line and the recognition sequence.
  Used to build a sequence map object
  */
  string db_line;
  string junk;
  for (int i = 0; i < 10; i++){
    getline(fin, junk);
  }

  while (getline(fin, db_line)) {
    db_line = db_line.substr(0, db_line.length()-2);
    string an_enz_acro, a_rec_seq;
    stringstream ss(db_line);
    getline(ss, an_enz_acro, '/');
    while (getline(ss, a_rec_seq, '/')) {
      SequenceMap new_sequence_map(a_rec_seq, an_enz_acro);
      a_tree.insert(new_sequence_map);
    }
  }
  fin.close();
  //a_tree.printTree();

/* Allows for user input so they can choose what file becomes the input file and
build a tree */
string input_str;
while (cin >> input_str){
  SequenceMap sequence_input(input_str, " ");
  cout << a_tree.contains(sequence_input) << endl;
}}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  cout << "Input filename is " << db_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap> .
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);

  return 0;
}
