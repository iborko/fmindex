#include "../include/BWTransform.h"

std::string BWTransform::transform(const std::string& s) {
    std::vector<StringRotator*> v;
    v.reserve(s.size());

    StringRotator* lastStringRotator = NULL;
    for (size_t i = 0; i < s.size(); i++) {
        StringRotator* current;
        if (lastStringRotator == NULL)
            current = new StringRotator(s);
        else
            current = new StringRotator(*lastStringRotator);

        current->rotate();
        v.push_back(current);
        lastStringRotator = current;
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
