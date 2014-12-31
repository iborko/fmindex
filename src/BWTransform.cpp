#include "../include/BWTransform.h"

std::string BWTransform::transform(const std::string& s) {
    std::vector<StringRotator*> v;
    v.reserve(s.size());

    for (size_t i = 0; i < s.size(); i++) {
        v.push_back(new StringRotator(s));
        v[i]->rotate(i);
    }

    std::sort(v.begin(), v.end(), ValueComparer<StringRotator>());

    std::string result;
    for (size_t i = 0; i < v.size(); i++) {
        result.push_back(v[i]->get_last_char());
        delete v[i];
    }

    return result;
}

std::string BWTransform::reverse(
    const std::string& bwt_text,
    const OccurrenceTableInterface& occ_table,
    const PrefixSumTableInterface& ps_table) {

    std::string original_reversed;
    int pos = 0;
    for(size_t i = 0; i < bwt_text.size() - 1; i++) {
        char c = bwt_text[pos];
        original_reversed.push_back(c);
        // L-F mapping to get new position
        pos = ps_table.get_C(c) + occ_table.get_occ(c, pos);
    }

    std::reverse(original_reversed.begin(), original_reversed.end());
    return original_reversed;
}

std::vector<int>  BWTransform::search(
        const std::string& pattern,
        const std::vector<int>& alph,
        const int * sa,
        const OccurrenceTableInterface& occ_table,
        const PrefixSumTableInterface& ps_table) {

    //counting phase
    int i = pattern.size() - 1;
    char c = pattern[i];

    std::vector<int>::const_iterator it = std::find(alph.begin(), alph.end(), c);

    int sp = ps_table.get_C(c);
    int ep;

    if (it == alph.end() - 1){
        ep = sizeof(sa);
    }
    else{
        ep = ps_table.get_C(char(*(++it)));
    }

    while (sp <= ep && i >= 1){
        c = pattern[i - 1];

        sp = ps_table.get_C(c) + occ_table.get_occ(c, sp);
        ep = ps_table.get_C(c) + occ_table.get_occ(c, ep);

        i--;

    }

    //localizing phase
    std::vector<int> occ_indices;

    for (size_t i = sp; i < ep; i++){
        occ_indices.push_back(sa[i]);
    }

    return occ_indices;
}
