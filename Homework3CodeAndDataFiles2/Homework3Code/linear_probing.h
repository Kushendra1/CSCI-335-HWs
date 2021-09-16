/*Kushendra Ramrup
4/2/2020
Professor Raja
CSCI 335

Linear Probing File
Made in order to have a linera probing hashing machanism for the project, it is made from the porvided
quadratic probing file provided where the only real changes I made were to the FindPos function - where the
probing actually occurs- by taking out the offset increment to set it to a linear probe rather than a
quadratic.*/

#pragma once

template <typename HashedObj>
class HashTableLinear {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableLinear(size_t size = 101) : array_(NextPrime(size))
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
    // Insert x as active                                      collisions is also passed by ref in all related funcs to Insert
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

  bool Insert(HashedObj && x, int & collisions) {           //modified the original insert func provided so that it passes collision by reference to keep track of collisions
    // Insert x as active                                   collisions is also passed by ref in all related funcs to Insert
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

  bool Remove(const HashedObj & x, int & collisions) {    ////modified the original remove func provided so that it passes collision by reference to keep track of collisions
    size_t current_pos = FindPos(x, collisions);          //collisions is also passed by ref in all related funcs to Remove
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  int get_items() {                //Just a public function to access the private info - size of table
    return current_size_;
  }

  int get_Size() {                 //Just a public function to access the private info - size of array
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

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x, int & collisions) const {   //modified the original FindPos func provided so that it passes collision by reference to keep track of collisions
    size_t offset = 1;
    size_t current_pos = InternalHash(x);

    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      collisions += 1;                                            //this is where collisions occur so it is incremented here
      current_pos += offset;                                      //Since it is linear probing there's no need for the incrementing the offset
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }

    return current_pos;
  }

  void Rehash(int & collisions) {                                //modified the original rehash to pass collision by reference and keep track of it
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
