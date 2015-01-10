#include "../include/PrefixSumTable.h"

PrefixSumTable::PrefixSumTable(const std::string& s) {

    std::string::const_iterator string_it = s.begin();
    for( ; string_it != s.end(); string_it++) {
        // update sum of current character +1
        if (sum_map_.find(*string_it) == sum_map_.end())
            sum_map_[*string_it] = 0;
        sum_map_[*string_it]++;
    }
    
    // every sum has to be sum of all smaller characters
    int currentSum = 0;
    SumMap::iterator map_it = sum_map_.begin();
    for( ; map_it != sum_map_.end(); map_it++) {
        // update current item with cumulative sum
        int itemSum = map_it->second;
        map_it->second = currentSum;
        
        currentSum += itemSum;
    }
}

int PrefixSumTable::get_C(char c) const {
    SumMap::const_iterator map_it = sum_map_.find(c);
    if (map_it == sum_map_.end()) {
        return 0;
    }

    return map_it->second;
}
