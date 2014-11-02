#ifndef PREFIXSUMTABLE_H_
#define PREFIXSUMTABLE_H_

#include <string>
#include <map>
#include <iostream>

#include "PrefixSumTableInterface.h"

class PrefixSumTable : public PrefixSumTableInterface {
public:
    PrefixSumTable(const std::string&);
    ~PrefixSumTable() { }

    virtual int get_C(char) const;

private:
    typedef std::map<char, int> SumMap;
    SumMap sum_map_;
};

#endif
