#ifndef PREFIXSUMTABLEINTERFACE_H_
#define PREFIXSUMTABLEINTERFACE_H_

class PrefixSumTableInterface {
public:
    virtual ~PrefixSumTableInterface() { }
    
    // gets number of characters smaller than c in given text
    virtual int get_C(char) const = 0;
};

#endif
