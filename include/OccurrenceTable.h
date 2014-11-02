#ifndef OCCURRENCETABLE_H_
#define OCCURRENCETABLE_H_

#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "OccurrenceTableInterface.h"

class OccurrenceTable : public OccurrenceTableInterface {
public:
    OccurrenceTable(const std::string&);
    virtual ~OccurrenceTable() { }

    virtual int get_occ(char c, int p) const;

private:
    typedef std::vector<int> IntVector;
    typedef std::map<char, std::vector<int> > OccMap;
    
    OccMap occ_map_;
};

#endif
