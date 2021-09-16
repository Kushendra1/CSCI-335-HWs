/*Kushendra Ramrup
4/2/2020
Professor Raja
CSCI 335

Quadratic Probing File
Made in order to have a quadratic probing hashing machanism for the project, it is provided
with the other code for the project. The only real changes I made were to the FindPos function - where the
probing actually occurs- insert, remove, rehash funcs by adding the extra parameter collsions and passing it
by reference so that I can keep track of the number of collisions when probing. I also added to accessor funcs
in the get_items and get_size in order to provide the number of items in the hash table at any moment and
the size of said hash table. */

#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <math.h>

namespace {

// Internal method to test if a positive number is prime.
bool IsPrime(size_t n) {
  if( n == 2 || n == 3 )
    return true;

  if( n == 1 || n % 2 == 0 )
    return false;

  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;

  return true;
}


// Internal method to return a prime number at least as large as n.
int NextPrime(size_t n) {
  if (n % 2 == 0)
    ++n;
  while (!IsPrime(n)) n += 2;
  return n;
}

}  // namespace


// Quadratic probing implementation.
template <typename HashedObj>
class HashTable {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTable(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); }

  bool Contains(const HashedObj & x, int & collisions) const {
    return IsActive(FindPos(x, collisions));
  }

  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x, int & collisions) {       //modified the original insert func provided so that it passes collision by reference to keep track of collisions
    // Insert x as active                                    collisions is also passed by ref in all related funcs to Insert
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

  bool Insert(HashedObj && x, int & collisions) {      //modified the original insert func provided so that it passes collision by reference to keep track of collisions
    // Insert x as active                              collisions is also passed by ref in all related funcs to Insert
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

  bool Remove(const HashedObj & x, int & collisions) {   //modified the original insert func provided so that it passes collision by reference to keep track of collisions
    size_t current_pos = FindPos(x, collisions);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  int get_items() {                       //accessor func that returns the current amount of items in the hash table
    return current_size_;
  }

  int get_Size() {                       //accessor dunc that returns the current size of the hash table
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

  //int probes = 0;
  //int collisions = 0;

  std::vector<HashEntry> array_;
  size_t current_size_;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x, int & collisions) const {      //modified the original insert func provided so that it passes collision by reference to keep track of collisions
    size_t offset = 1;
    size_t current_pos = InternalHash(x);

    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      collisions += 1;                                              //collisions is incremented here as this is where the probing occurs
      current_pos += offset;  // Compute ith probe.
      offset += 2;
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    //collisions++
    //current_pos = current_pos % array_.size();
    return current_pos;
  }

  void Rehash(int & collisions) {                                  //modified the original insert func provided so that it passes collision by reference to keep track of collisions
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
};

#endif  // QUADRATIC_PROBING_H
