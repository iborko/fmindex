#ifndef SUFFIXARRAY_H
#define SUFFIXARRAY_H

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>

#include "sais.h"

typedef std::vector<int> IntVector;

class SuffixArray
{
public:
    // generate suffix array of string s
    static IntVector get_sa(const std::string& s);
    static std::string bwt(const std::string& s);
};

#endif // SUFFIXARRAY_H
