#ifndef FMINDEX_H_
#define FMINDEX_H_

#include <string>
#include <vector>
#include <algorithm>
#include "OccurrenceTableInterface.h"
#include "PrefixSumTableInterface.h"

std::vector<int> search(
        const std::string& pattern,
        const std::vector<char>& alph,
        const int* sa,
        const OccurrenceTableInterface& occ_table,
        const PrefixSumTableInterface& ps_table) {

    //counting phase
    int i = pattern.size() - 1;
    char c = pattern[i];

    std::vector<char>::const_iterator it = std::find(alph.begin(), alph.end(), c);

    int sp = ps_table.get_C(c);
    int ep;

    if (it == alph.end() - 1) {
        ep = sizeof(sa);
    }
    else {
        ep = ps_table.get_C(*(++it));
    }

    while (sp <= ep && i >= 1) {
        c = pattern[i - 1];

        sp = ps_table.get_C(c) + occ_table.get_occ(c, sp);
        ep = ps_table.get_C(c) + occ_table.get_occ(c, ep);

        i--;
    }

    //localizing phase
    std::vector<int> occ_indices;

    for (size_t i = sp; i < ep; i++) {
        occ_indices.push_back(sa[i]);
    }

    return occ_indices;
}

#endif
