#ifndef WAVELETTREE_H_
#define WAVELETTREE_H_

#include "OccurrenceTableInterface.h"
#include "BitStringRank.h"

#include <vector>
#include <set>
#include <map>
#include <cstdlib>  // int abs(int x);
#include <stdexcept>
#include <iostream>

typedef unsigned int UInt;
typedef std::set<char> CharSet;
typedef std::map<char, UInt> CharIntMap;
typedef std::vector<UInt> UIntVector;


class WaveletTree : public OccurrenceTableInterface {
public:
    // s - the string that tree should represent
    WaveletTree(const std::string& s, UInt bucket_size);
    virtual ~WaveletTree();

    // get number of occurences of char c until position p
    virtual int get_occ(char c, int p) const;

private:
    struct Node {
        Node(const BitVector& bit_vector, UInt bucket_size)
            : bit_string(bit_vector, bucket_size) { }
        char pivot;
        BitStringRank bit_string;
        Node* left_node;
        Node* right_node;
    };

    Node* root_;
    UInt bucket_size_;

    // Calculates the ideal pivot given an alphabet and character counts.
    // The ideal pivot is such that will give the least difference of the
    // number of characters that are less then pivot and those that are
    // greater or equal to the pivot
    // alph - all the characters, sorted ascending
    char calc_pivot(const std::string& alph, const CharIntMap& counts);
    
    // construct a binary WaveletTree
    // recursive
    // method deletes object str points to
    Node* create_node(const std::string* str, const std::string& alph,
        const CharIntMap& counts);
};

#endif
