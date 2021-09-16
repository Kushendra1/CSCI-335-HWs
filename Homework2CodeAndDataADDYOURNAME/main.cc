//#include "sequence_map.cc"
#include "HW2Q1.cc"
#include "query_tree.cc"
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v{1,2,3,4};
  v.push_back(0);
  v.push_back(1);
  v.push_back(3);
  v.push_back(5);

  cout << *my_find(v.begin(),v.end(), 4);
  return 0;
}
