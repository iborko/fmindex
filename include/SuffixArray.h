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
    static IntVector get_sa(const std::string& s, int n);
};

#endif // SUFFIXARRAY_H
