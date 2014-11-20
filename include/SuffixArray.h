#ifndef SUFFIXARRAY_H
#define SUFFIXARRAY_H

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "sais.h"

class SuffixArray
{
public:
    static int* get_sa(const std::string& s, int n);

};

#endif // SUFFIXARRAY_H
