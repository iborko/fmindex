#include "../include/OccurrenceTable.h"

OccurrenceTable::OccurrenceTable(const std::string& s) {
    std::string::const_iterator it = s.begin();
    int location = 0;
    for( ; it != s.end(); it++) {
        const char c = *it;
        occ_map_[c].push_back(location);
        location++;
    }
}

int OccurrenceTable::get_occ(char c, int p) const {
    // std::cout << "Occurrence of " << c << " is :";
    if (occ_map_.find(c) == occ_map_.end()) {
        // std::cout << 0 << std::endl;
        return 0; 
    }

    const IntVector& v = (occ_map_.find(c))->second;
    // occurrence is number of indexes (of char c) lesser than p
    int occurrence = 0;
    IntVector::const_iterator it = v.begin();
    for( ; it != v.end(); it++) {
        if (*it >= p)
            break;
        occurrence++;
    }

    // std::cout << occurrence << std::endl;
    return occurrence;
}
