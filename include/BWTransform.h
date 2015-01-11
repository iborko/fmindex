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

class BWTransform {
public:
    static std::string transform(const std::string& );

    static std::string reverse(
        const std::string& bwt_text,
        const OccurrenceTableInterface& occ_table,
        const PrefixSumTableInterface& ps_table);
};

#endif
