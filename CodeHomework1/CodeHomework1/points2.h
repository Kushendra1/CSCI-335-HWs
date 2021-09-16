// --> Kushendra Ramrup
/* A class Points2 that holds an array of coordinates, essentially the class is an array
of multiple subarrays. It has private variables seqence, an array of points, and size the size of sequence.
functions in the class like the big five, copy constructor,
copy assignment, move constructor, move assignment, and the destructor. There are also
the overload operators [] which returns a locatoion of a point, + which provides the sum of
2 subarrays, << which prints out the seuence of points, and = which serves as the copy assignment.
 */

#ifndef CSCI335_HOMEWORK1_POINTS2_H_
#define CSCI335_HOMEWORK1_POINTS2_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {
/* A class Points2 that holds an array of coordinates, essentially the class is an array
of multiple subarrays.
@Points2() the zero paramter constructor, when called creates and empty class Object
@Points2(const Points2 &rhs) the copy constructor, makes a deep copy of a points2 object into a new one
@Points2& operator=(const Points2 &rhs) copy assignment, overloads the = operator and sets obejec of left to deep copy of
object on right
@Points2(Points2 &&rhs) Move constructor, allows the rvalue object to be moved to an lvalue without making a copy
@Points2& operator=(Points2 &&rhs) Move assignment, used to transfer a temporary object into an existing one
@~Points2() desructor, deletes points2 object */
template<typename Object>
class Points2 {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.

  // Zero-parameter constructor.
  // Set size to 0.
  Points2() {
    size_ = 0;
    sequence_ = new std::array<Object, 2>[0];
  }

  // Copy-constructor.
  Points2(const Points2 &rhs) {
    size_ = rhs.size_; //copy size into the new object
    sequence_ = new std::array<Object, 2> [size_]; //allocating size for the for loop
    for (int i = 0; i < rhs.size_; i++){
      sequence_[i] = rhs.sequence_[i]; //copying each value at the index into a array
    }
  }

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  Points2& operator=(const Points2 &rhs) {  //overloading the equals operator
    if (this == &rhs) {
      return *this;
    }
    this->size_ = rhs.size_; //allocates size to the copy
    delete[] this->sequence_;
    /*
      you were missing this line here. you deleted the sequence
      and starting making changes to memory you didn't own anymore.
      you forgot to allocate new memory after deleting
    */
    this->sequence_ = new std::array<Object, 2>[this->size_];
    for (int i = 0; i < this->size_; i++){
      this->sequence_[i][0] = rhs.sequence_[i][0]; //copying each value at the index into a array
      this->sequence_[i][1] = rhs.sequence_[i][1];
    }
    return *this;
  }

  // Move-constructor.
  Points2(Points2 &&rhs){
    size_ = rhs.size_; //points the new pointer to the size of original
    rhs.size_ = 0;
    sequence_ = rhs.sequence_;  //gives size a new pointer in this
    rhs.sequence_ = nullptr;  //deallocating memory of original pointer
  }

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2& operator=(Points2 &&rhs) {
    std::swap(this->size_, rhs.size_);  //swap contents
    std::swap(this->sequence_, rhs.sequence_);
    return *this;
  }

  ~Points2(){
    this->size_ = 0;    //just resetting size and deleting everything
    delete[] this->sequence_;
    this->sequence_ = nullptr; //set pointer to null
  }

  // End of big-five.

  // One parameter constructor.
  Points2(const std::array<Object, 2>& item) {
    size_ = 1; //only passing 1 subarray
    sequence_ = new std::array<Object, 2> [size_]; //allocating space for the new object that was created
    sequence_[0] = item;  //adds item to the sequence array
  }

  // Read a chain from standard input.
  void ReadPoints2() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line);
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;
    // Allocate space for sequence.
    size_ = size_of_sequence;
    sequence_ = new std::array<Object, 2> [size_];
    // Add code here.

    Object token; //allows us to read only int or doubles, ignores other info
    int x_variable;
    int y_variable;
    for (int i = 0 ;input_stream >> token; ++i) {
      // Read coordinates.
      // Fill sequence_ here.
      y_variable = i%2; //if i is an even number, put it in the second part of the sub array
      x_variable = i/2;
      sequence_[x_variable][y_variable] = token; //taking the data we stored from files an placing into sub array
    }

  }

  size_t size() const {
    return size_;
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const {
    if (location >= size_ || location < 0){
      abort();
    }
    else {
      return sequence_[location];
    }
  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
 friend Points2 operator+(const Points2 &c1, const Points2 &c2) {
   Points2<Object> sum;
   if (c1.size() > c2.size()) {
     sum.size_ = c1.size();
     sum.sequence_ = new std::array<Object, 2> [c1.size()]; //create new array and allocate space for the sum
     for (int i = 0; i < c2.size(); i++){
       sum.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];  //add the values of the two arrays together and store in new array
       sum.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
     }
     for (int i = c2.size(); i < c1.size(); i++) {
       sum.sequence_[i][0] = c1.sequence_[i][0]; //since c1 is bigger, just transfer remaining values into the new array
       sum.sequence_[i][1] = c1.sequence_[i][1];
     }
   }
   else {
     sum.size_ = c2.size();
     sum.sequence_ = new std::array<Object, 2> [c2.size()]; //create new array and allocate space for the sum
     for (int i = 0; i < c2.size(); i++) {
       sum.sequence_[i][0] = c2.sequence_[i][0] + c1.sequence_[i][0];
       sum.sequence_[i][0] = c2.sequence_[i][1] + c1.sequence_[i][1];
     }
     for (int i = c1.size(); i < c1.size(); i++) {
       sum.sequence_[i][0] = c2.sequence_[i][0]; //since c2 is bigger, just transfer remaining values into the new array
       sum.sequence_[i][1] = c2.sequence_[i][1];
     }
   }
   return sum;
 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Points2 &some_points2) {
   if (some_points2.size_ == 0) {
    out << "() ";
    return out;
   }
   for (int i = 0; i < some_points2.size_; i++) {
     out<< "(" << some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1] << ") "; //prints out the array in specific format
   }
   return out;
 }

 private:
  // Sequence of points.
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2_H_
