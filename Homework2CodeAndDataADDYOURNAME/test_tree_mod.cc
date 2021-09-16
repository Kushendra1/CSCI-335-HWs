// Kushendra Ramrup
// CSCI 335
//Professor Anita Raja
//Assignment 2 Question 2 Part C

/* Performs the same routine as in test_tree.cc and the modified part is in
avl_tree_p2c.h */

#include "avl_tree_p2c.h"
#include "sequence_map.h"

// You will have to add #include "sequence_map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)
  std::ifstream fin(db_filename.c_str());
  if (fin.fail()) {
    std::cerr << "File cannot be opened for reading." << std::endl;  //error message to be displayed if file can't be read/opened
    exit(1);
  }

  //AvlTree<SequenceMap> a_tree;
  string db_line;
  string junk;
  for (int i = 0; i < 10; i++){
    getline(fin, junk);
  }

//Building an AVl tree a_Tree from the input file
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


//Prints the number of nodes in a_tree
//Computes the average depth of search tree and prints it
//Computes and prints the ratio of average depth to log base 2 of n.
  float log_count = log2 (a_tree.tree_count());
  int treecount = a_tree.tree_count();
  cout << "2: " << a_tree.tree_count()  << endl;
  cout << "3a: " << a_tree.AverageDepth() << endl;
  cout << "3b: " << (a_tree.AverageDepth() / (log2(a_tree.tree_count()))) << endl;

  fin.close();
//Searches the tree for each string in the sequences.txt file and counts the
//total number of recursive calls for all executions
//Prints the average number of recursions calls
  std::ifstream fin_new(seq_filename.c_str());
  if (fin_new.fail()) {
    std::cerr << "File cannot be opened for reading." << std::endl;  //error message to be displayed if file can't be read/opened
    exit(1);
  }

  string seq_line;
  float recursive_count = 0;
  float query_count = 0;
  float count = 0;
  float r_count = 0;
  string input_str;
  // while (getline (fin_new, seq_line)){
  //   query_count++;
  //   SequenceMap sequence_input(seq_line, " ");
  //   if (a_tree.contains(sequence_input, recursive_count).get_rec_seg() != "Not Found"){
  //     count++;
  //   }
  // }
  std::vector<SequenceMap> v;
  while (getline (fin_new, seq_line)){
    SequenceMap sequence_input(seq_line, " ");
    v.push_back(sequence_input);
  }

  for(int i = 0; i < v.size(); i++){
    if (a_tree.contains(v[i], recursive_count).get_rec_seg() != "Not Found"){
         count++;
       }
  }

  float average_count = recursive_count/v.size();

  cout << "4a: " << count  << endl;
  cout << "4b: " << average_count << endl;

  fin_new.close();

  //Removes every other sequence in sequences.txt from the tree and counts the total
  //number of recursion calls for all executions of remove()

  int remove_success = 0;
  float recursive_calls_r = 0;
  float remove_calls = v.size()/2;

  // string sequence;
  // while(getline(fin_another, seq_line)) {
  //     query_count_r++;
  //     SequenceMap search_sequence(seq_line, "");
  //     if (query_count_r % 2 == 1 && a_tree.contains_bool_version(search_sequence)) {
  //         recursive_calls_r+=a_tree.remove(search_sequence);
  //         remove_calls++;
  //     }
  // }

  for (int i = 0; i< v.size(); i+=2){
    a_tree.remove(v[i], recursive_calls_r);
  }

  float initial_nodes = a_tree.tree_count();
  remove_success = treecount - initial_nodes;
  float recursion_calls_avg = recursive_calls_r/remove_calls;
//  cout << recursive_calls_r << " " << remove_calls << endl;
  cout << "5a: " << remove_success  <<endl;
  cout << "5b: " << recursion_calls_avg  <<endl;
  cout << "6a: " << a_tree.tree_count()  <<endl;
  cout << "6b: " << a_tree.AverageDepth()  <<endl;
  cout << "6c: " << (a_tree.AverageDepth() / (log2(a_tree.tree_count()))) << endl;

}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);

  return 0;
}
