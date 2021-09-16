/* Kushendra Ramrup
CSCI 335
Professor Raja
Final Exam

Given the sizes of several matrices, calculate the optimal multiplication ordering using dynamic
programming. The sizes will be presented in a file containing dimensions in a sequence.
Write a program that runs as follows:
./optimal_multiplications <dimensions_file>
The program should produce the optimal number of multiplications.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

/* The function openFile is used for opening input files, taking in the string
@filename of a txt file and returning @input a filestream. If it fails to open the input
and eroor message will be delivered. */
ifstream openFile(const string filename) {
  ifstream input;
  input.open(filename);
  if(input.fail()) {
    cout << "Cannot read from " << filename;
    exit(1);
  }
  return input;
}

/* The function make_vector is used for converting the contents of the input file
which has strings of numbers, into a vector of integers. It takes in a string @filename
and the returns the vector @numbers
*/
vector <int> make_vector(const string filename) {
  vector <int> numbers;
  ifstream Input = openFile(filename);
  string line;
  while(getline(Input, line)) {      //read through the txt file and insert int versions of the strings into the vector
    numbers.push_back(stoi(line));
  }
  return numbers;
}

/* The function matrix_multiplication, when given  the sizes of several matrices, calculates
the optimal multiplication ordering using dynamic programming. It is based off of the pseudo
code provided from the Lecture 23 folder, in the "Chain Matrix Multiplication Reference" pdf.
It takes in an int array @array and an int @array_size, the size of the array. It returns
an int variable from the matrix made in function as the result from the multiplication.
*/
int matrix_multiplication(int array[], int array_size) {
  // ifstream Input = openFile(filename);
  // int numbers[5];
  // for (int i = 0; i < 5; i++){
  //   Input >> numbers[i];
  // }
  int matrix[array_size][array_size];   //initialize a matrix to store int values, with 0s as the intial row,
  for (int i = 1; i < array_size; i++) {  //column, and diagonal values
    matrix[i][i] = 0;
  }
  int diag;
  for (diag = 2; diag < array_size; diag++) { //diag represents the diagonal going through the matrix table
    for (int i = 1; i < array_size - diag + 1; i++) {  //i is the rows.
      int sum = i + diag - 1;
      matrix[i][sum] = INT_MAX;
      for (int iterator = i; iterator <= sum - 1; iterator++) {
        //dynamic programing formula for finding the minimum number of multiplications
        int multiplications = matrix[i][iterator] + matrix[iterator + 1][sum] + array[i - 1] * array[iterator] * array[sum];
        if (multiplications < matrix[i][sum]) {
          matrix[i][sum] = multiplications;
        }
      }
    }
  }
  return matrix[1][array_size - 1];
}

int multiplication_driver(int argc, char **argv) {
    //Please place all functionality in here instead of the main.
    //Feel free to make any functions or objects you wish, as long as we only call this function.
    const string dimension_filename(argv[1]);
    vector <int> numbers = make_vector(dimension_filename);

    /* The next two lines of code are used to convert the vecto of integer @numbers
    made from the inputed text file using the make_vector function, into an array @arr
    so that it can be inputed into the matrix_multiplication function.*/
    int arr[numbers.size()];
    copy(numbers.begin(), numbers.end(), arr);

    cout<< matrix_multiplication(arr, numbers.size()) << endl;
}

int main(int argc, char **argv) {
    if (argc != 2) {
		cout << "Usage: " << argv[0] << "<dimensions_file>" << endl;
		return 0;
    }

    multiplication_driver(argc, argv);

    return 0;
}
