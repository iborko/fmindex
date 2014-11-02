#include "../include/PrefixSumTable.h"

PrefixSumTable::PrefixSumTable(const std::string& s) {
    std::string::const_iterator it = s.begin();
    for( ; it != s.end(); it++) {
        if (sum_map_.find(*it) == sum_map_.end())
            sum_map_[*it] = 0;
        sum_map_[*it]++;
    }
}

int PrefixSumTable::get_C(char c) const {
    // std::cout << "C of " << c << " is :";
    if (sum_map_.find(c) == sum_map_.end()) {
        // std::cout << 0 << std::endl;
        return 0;
    }

    int sum = 0;
    SumMap::const_iterator it = sum_map_.begin();
    for( ; it != sum_map_.end(); it++) {
        if (it->first == c)
            break;
        sum += it->second;
    }

    // std::cout << sum << std::endl;
    return sum;
}
