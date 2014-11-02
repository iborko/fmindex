#ifndef OCCURRENCETABLEINTERFACE_H_
#define OCCURRENCETABLEINTERFACE_H_

class OccurrenceTableInterface {
public:
    virtual ~OccurrenceTableInterface() { }

    // get number of occurences of char c until position p
    virtual int get_occ(char c, int p) const = 0;
};

#endif
