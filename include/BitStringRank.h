#ifndef BITSTRINGRANK_H_
#define BITSTRINGRANK_H_

#include <vector>
#include <cassert>
#include <iostream>

// NOTE: change types to match your bucket_size needs
typedef unsigned int SuperbucketType;
typedef unsigned short int BucketType;

typedef std::vector<bool> BitVector;
typedef unsigned int UInt;
typedef std::vector<SuperbucketType> SuperbucketVector;
typedef std::vector<BucketType> BucketVector;


class BitStringRank {
public:
    BitStringRank(const BitVector& bit_string, UInt bucket_size);

    // returns the number of bits set (having the value 1) in the first i
    // bits of this bit string
    UInt rank(UInt i);

private:
    UInt _bucket_size;
    UInt _length;
    BitVector _bit_vector;
    SuperbucketVector _superbuckets;
    BucketVector _buckets;
};

#endif
