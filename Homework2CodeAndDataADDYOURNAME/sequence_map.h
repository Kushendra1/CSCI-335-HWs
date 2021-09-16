//Kushendra Ramrup
//CSCI 335
//Professor Anita Raja
//Assignment 2 Question 1

#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class SequenceMap {
  public:
    // Default "big five" --
    // Zero-parameter constructor.
    SequenceMap() = default;

    // Copy-constructor.
    SequenceMap(const SequenceMap &rhs) = default;

    // Copy-assignment.
    SequenceMap& operator=(const SequenceMap &rhs) = default;

    // Move-constructor.
    SequenceMap(SequenceMap& rhs) = default;

    // Move-assignment.
    SequenceMap& operator=(SequenceMap& rhs) = default;

    //Destructor
    ~SequenceMap() = default;

    // End of big-five.

    // two-parameter constructor; constructs SequenceMap object from string 2 parameters
    SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro) {
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back(an_enz_acro); // private member will contain one element
    }

    // comparison between rhs and recognition_sequence_
    //operates based on the regular string comparison between the recognition_sequence_ strings
    bool operator<(const SequenceMap &rhs) const {
        if (this->recognition_sequence_ < rhs.recognition_sequence_) {
            return true;
        }
        return false;
        // return recognition_sequence_.compare(rhs.recognition_sequence_);
    }

    // overloading the << operator to print enzyme_acronyms vector for a given recognition sequence
    friend std::ostream &operator<<(std::ostream &out, const SequenceMap &seqMap) {
        for (int i = 0; i < seqMap.enzyme_acronyms_.size(); i++) {
            out << seqMap.enzyme_acronyms_[i];
        }
        return out;
    }

    // assumes that other_sequence.recognition_sequence_ are equal
    // other_sequence will not be affected and enzyme_acronyms will be appended
    //produces a vector of two objects
    void Merge(const SequenceMap &other_sequence) {
        std::vector<std::string> &v1 = enzyme_acronyms_;
        std::vector<std::string> v2 = other_sequence.enzyme_acronyms_;

        for (int i = 0; i < v2.size(); i++) {
            v1.push_back(" ");
            v1.push_back(v2[i]);
        }
      }

    std::string get_rec_seg() {
      return recognition_sequence_;
    }

  private:

    std::string recognition_sequence_ ;
    std::vector<std::string> enzyme_acronyms_;
};
