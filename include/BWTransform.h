#ifndef BWTRANSFORM_H_
#define BWTRANSFORM_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "StringRotator.h"
#include "functors.h"
#include "OccurrenceTableInterface.h"
#include "PrefixSumTableInterface.h"

// class that implements Burrows-Wheeler transformation and reversing
class BWTransform {
public:
    // burrows-wheeler transformation of given string
    static std::string transform(const std::string& );

    // reversing burrows-wheeler transform using occurrence table and
    // prefix sum table
    static std::string reverse(
        const std::string& bwt_text,
        const OccurrenceTableInterface& occ_table,
        const PrefixSumTableInterface& ps_table);
};

#endif
