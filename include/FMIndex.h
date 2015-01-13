#ifndef FMINDEX_H_
#define FMINDEX_H_

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include "OccurrenceTableInterface.h"
#include "PrefixSumTableInterface.h"

std::vector<int> search(
        const std::string& pattern,
        const std::vector<char>& alph,
        const std::vector<int>& sa,
        const OccurrenceTableInterface& occ_table,
        const PrefixSumTableInterface& ps_table) {

    //counting phase
    int i = pattern.size() - 1;
    char c = pattern[i];

    size_t sp = ps_table.get_C(c);
    size_t ep;

    std::vector<char>::const_iterator it = std::find(alph.begin(), alph.end(), c);
    if (it == alph.end() - 1) {
        ep = sa.size();
    }
    else {
        ep = ps_table.get_C(*(it + 1));
    }

    while (sp <= ep && i >= 1) {
        i--;
        c = pattern[i];

        sp = ps_table.get_C(c) + occ_table.get_occ(c, sp);
        ep = ps_table.get_C(c) + occ_table.get_occ(c, ep);
    }

    assert(sp <= sa.size());
    assert(ep <= sa.size());

    //localizing phase
    std::vector<int> occ_indices;
    for (size_t i = sp; i < ep; i++) {
        occ_indices.push_back(sa[i]);
    }

    return occ_indices;
}

#endif
