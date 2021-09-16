// Homework 4
// Testing Sorting Algorithms
// Kushendra Ramrup

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Test function that shows how you can time a piece of code.
// Just times a simple loop.

void TestTiming() {
  //cout << "Test Timing" << endl;
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i) sum ++;
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now();
  //cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns" << endl;
  //cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;

}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
  // Use rand() to generate random integer
  vector<int> random_vector(size_of_vector);
  srand(time(NULL));
  for (int i = 0; i < size_of_vector; i++){
    int j = rand() % 100+1;
    random_vector[i] = j;
  }
  return random_vector;
}

// Generate and returns sorted vecotr of size @size_of_vector
// If smaller_to_larger is true, returns vector sorted from small to large
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
  vector<int> sorted_vector(size_of_vector);
  if (smaller_to_larger){
    for (int i = 0; i< size_of_vector; i++){
      sorted_vector[i] = i; //unlinke the random vec where each index is a random number, here each index is just the number of the index+1
    }
    return sorted_vector;
  }
  else{
    for (int i = 0; i < size_of_vector; i++){
      sorted_vector[i] = size_of_vector;
      size_of_vector --;
    }
    return sorted_vector;
  }
}

// Verifies that a vector is sorted given a comparator
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {
  for(int i = 1; i < input.size(); i++){ //goes through each element of vector and checks if they are sorted. If an input that is greater than it's previous is actuall smaller, then it isnt sorted
    if(less_than(input[i], input[i-1])){
      return false;
    }
  }
  return true;
}

// Computes duration given a start time and a stop time in nano seconds
auto ComputeDuration(chrono::high_resolution_clock::time_point start_time, chrono::high_resolution_clock::time_point end_time) {
  return (end_time - start_time).count();
}

// Wrapper function to test different sorting algorithms
void sortTestingWrapper(int argc, char **argv) {
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
    cout << "Invalid input type" << endl;
    return;
  }
  if (input_size <= 0) {
    cout << "Invalid size" << endl;
    return;
  }
  if (comparison_type != "less" && comparison_type != "greater") {
    cout << "Invalid comparison type" << endl;
    return;
  }

  // This block of code to be removed for your final submission.
  TestTiming();

  cout << "Running sorting algorithms: " << input_type << " " << input_size <<  " " << comparison_type << endl;
  vector<int> input_vector;
  if (input_type == "random") {
    // Generate random vector
    input_vector = GenerateRandomVector(input_size);

  } else {
    if (input_type == "sorted_large_to_small"){
      input_vector = GenerateSortedVector(input_size, false);
    }
    else{
      input_vector = GenerateSortedVector(input_size, true);
    }
  }


  if (comparison_type == "less") {
   cout << "Heapsort" << endl << endl;
   auto begin = chrono::high_resolution_clock::now();
   HeapSort(input_vector, less<int>{});
   auto end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) <<endl << endl;

   cout << "MergeSort" << endl << endl;
   begin = chrono::high_resolution_clock::now();
   MergeSort(input_vector, less<int>{});
   end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) <<endl << endl;

   cout << "QuickSort" << endl << endl;
   begin = chrono::high_resolution_clock::now();
   QuickSort(input_vector, less<int>{});
   end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) <<endl << endl;

   cout << "Testing Quicksort Pivot Implementations" << endl << endl;
   cout << "Median of Three" << endl << endl;
   begin = chrono::high_resolution_clock::now();
   QuickSort(input_vector, less<int>{});
   end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) <<endl << endl;

   cout << "Middle" << endl << endl;
   QuickSort2(input_vector, less<int>{});
   end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) <<endl << endl;

   cout << "First" << endl << endl;
   begin = chrono::high_resolution_clock::now();
   QuickSort3(input_vector, less<int>{});
   end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) <<endl << endl;

 } else { //greatest -> least sorting
   //passes greater<int> as the comparator function
   cout << "Heapsort" << endl << endl;
   auto begin = chrono::high_resolution_clock::now();
   begin = chrono::high_resolution_clock::now();
   HeapSort(input_vector, greater<int>{});
   auto end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) <<endl << endl;

   cout << "MergeSort" << endl << endl;
   begin = chrono::high_resolution_clock::now();
   MergeSort(input_vector, greater<int>{});
   end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) <<endl << endl;


   cout << "QuickSort" << endl << endl;
   begin = chrono::high_resolution_clock::now();
   QuickSort(input_vector, greater<int>{});
   end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) <<endl << endl;

   cout << "Testing Quicksort Pivot Implementations" << endl << endl;
   cout << "Median of Three" << endl << endl;
   begin = chrono::high_resolution_clock::now();
   QuickSort(input_vector, greater<int>{});
   end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) <<endl << endl;

   cout << "Middle" << endl << endl;
   begin = chrono::high_resolution_clock::now();
   QuickSort2(input_vector, greater<int>{});
   end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) <<endl << endl;

   cout << "First" << endl << endl;
   begin = chrono::high_resolution_clock::now();
   QuickSort3(input_vector, greater<int>{});
   end = chrono::high_resolution_clock::now();
   cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
   std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) <<endl << endl;
 }
}

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }

  sortTestingWrapper(argc, argv);

  return 0;
}
