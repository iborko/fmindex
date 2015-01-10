#ifndef PREFIXSUMTABLE_H_
#define PREFIXSUMTABLE_H_

#include <string>
#include <map>
#include <iostream>

#include "PrefixSumTableInterface.h"

// Trivial implementation of the prefix sum table. The prefix-sum table
// of text T stores for every character c the number of characters
// smaller than c in T.
class PrefixSumTable : public PrefixSumTableInterface {
public:
    PrefixSumTable(const std::string&);
    ~PrefixSumTable() { }

    // returns the number of characters smaller than c
    virtual int get_C(char c) const;

private:
    typedef std::map<char, int> SumMap;
    // number of characters smaller than key (char)
    SumMap sum_map_;
};

#endif
