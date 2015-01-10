#include "../include/OccurrenceTable.h"

OccurrenceTable::OccurrenceTable(const std::string& s) {

    // set matrix[c, pos] to 1 if character c is on position pos
    for(size_t i = 0 ; i < s.size(); i++) {
        const char c = s[i];
        // if character c hasn't been seen before, init it's vector
        if (occ_map_.find(c) == occ_map_.end())
            occ_map_[c].resize(s.size(), 0);
        occ_map_[c][i] = 1;
    }

    // modify matrix so it contains number of occurences of character c up to
    // position i
    OccMap::iterator map_it = occ_map_.begin();
    for( ; map_it != occ_map_.end(); map_it++) {

        int sum = 0;
        // iterate through all indexes of char (map_it->first)
        IndexVector::iterator index_it = map_it->second.begin();
        for (; index_it != map_it->second.end(); index_it++) {
            int element = *index_it;
            *index_it = sum;
            sum += element;
        }
    }
}

int OccurrenceTable::get_occ(char c, int p) const {

    // find vector of occurences of characters c
    OccMap::const_iterator map_it = occ_map_.find(c);
    if (map_it == occ_map_.end()) {
        return 0; 
    }

    return (map_it->second)[p];
}
