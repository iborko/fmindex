#ifndef BWTRANSFORM_H_
#define BWTRANSFORM_H_

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

#include "StringRotator.h"
#include "functors.h"
#include "OccurrenceTableInterface.h"
#include "PrefixSumTableInterface.h"

class BWTransform {
public:
    static std::string transform(const std::string& );
    /* static int lf_mapping(
        const OccurrenceTableInterface& occ_table,
        const PrefixSumTableInterface& ps_table,
        char c); */
    static std::string reverse(
        const std::string& bwt_text,
        const OccurrenceTableInterface& occ_table,
        const PrefixSumTableInterface& ps_table);
};

#endif
