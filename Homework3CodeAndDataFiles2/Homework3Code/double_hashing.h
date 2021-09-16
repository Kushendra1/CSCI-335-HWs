/*Kushendra Ramrup
4/4/2020
Professor Raja
CSCI 335

Double Hashing File
Made in order to have a double hashing machanism for the project, it is made from the provided
quadratic probing file provided where the changes I made were adding a second hashing function
to the file - this one being (x) = R – (x mod R). The r values I used during testing were primes
smaller than the size of the hash table, so I just used the first set of prime numbers when counting: 3, 5, 7, 11, 13 etc.
The FindPos func then uses this second hashing function in order to be double hashing.
Also, collision is passed by reference in the FindPos and other related funcs in order to keep track of
the amount of collisions.*/

#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <math.h>

template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); }

  bool Contains(const HashedObj & x, int & collisions) const {
    return IsActive(FindPos(x, collisions));
  }

  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x, int & collisions) {    //modified the original insert func provided so that it passes collision by reference to keep track of collisions
    // Insert x as active
    size_t current_pos = FindPos(x, collisions);
    if (IsActive(current_pos)) {
      return false;
    }

    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash(collisions);
    return true;
  }

  bool Insert(HashedObj && x, int & collisions) {     //modified the original insert func provided so that it passes collision by reference to keep track of collisions
    // Insert x as active
    size_t current_pos = FindPos(x, collisions);
    if (IsActive(current_pos)) {
      return false;
    }

    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash(collisions);

    return true;
  }

  bool Remove(const HashedObj & x, int & collisions) {   //modified the original remove func provided so that it passes collision by reference to keep track of collisions
    size_t current_pos = FindPos(x, collisions);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  void r_val(int R) {       //accessor func that returns the r value used in the second hashing function
    R_ = R;
  }

  int get_items(){          //accessor func that returns the current amount of items in the hash table
    return current_size_;
  }

  int get_Size(){           //accessor func that returns the current size the hash table
    return array_.size();
  }

 private:
  struct HashEntry {
    HashedObj element_;
    EntryType info_;

    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }

    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };


  std::vector<HashEntry> array_;
  size_t current_size_;
  int R_= 0;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x, int & collisions) const {  //modified the original FindPos func provided so that it passes collision by reference to keep track of collisions
    size_t current_pos = InternalHash(x);
    size_t second_hash = second_InternalHash(x);             //second hashing func is called when a collision occurs

    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      current_pos += second_hash;
      collisions += 1;                                    //incrementing collisions int value
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }

    return current_pos;
  }

  void Rehash(int & collisions) {           //modified the original rehash func provided so that it passes collision by reference to keep track of collisions
    std::vector<HashEntry> old_array = array_;
    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;

    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_), collisions);
  }

  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }

  size_t second_InternalHash(const HashedObj x) const {   //the second hashing func to be used in double hashing based of the formula
    static std::hash<HashedObj> hf;                       //(x) = R – (x mod R)
    return R_ - (hf(x) % R_);
  }
};
