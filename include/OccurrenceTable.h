#ifndef OCCURRENCETABLE_H_
#define OCCURRENCETABLE_H_

#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "OccurrenceTableInterface.h"

// Trivial implementation of occurence table using matrix (alphabet,
// string length), implemented as map<char, vector<int> >
class OccurrenceTable : public OccurrenceTableInterface {
public:
    OccurrenceTable(const std::string&);
    virtual ~OccurrenceTable() { }

    // returns the number of occurences of char c up to position p
    virtual int get_occ(char c, int p) const;

private:
    typedef std::vector<int> IndexVector;
    typedef std::map<char, IndexVector > OccMap;
    
    OccMap occ_map_;
};

#endif
