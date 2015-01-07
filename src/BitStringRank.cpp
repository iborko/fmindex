#include "../include/BitStringRank.h"

BitStringRank::BitStringRank(const BitVector& bit_vector, UInt bucket_size)
    : _bucket_size(bucket_size), _bit_vector(bit_vector) {

    // bucket_size < 2^(BucketType bit number)
    assert(bucket_size < (1 << (sizeof(BucketType) * 8)));

    this->_length = bit_vector.size();
    //std::cout << "-- Creatin new BitStringRank" << std::endl;
    //std::cout << "Bit vector has size of " << _length << std::endl;
    
    // fill with zeros
    this->_buckets.resize(_length / _bucket_size + 1, 0);
    this->_superbuckets.resize(_length / (_bucket_size * _bucket_size) + 1, 0);
    //std::cout << "BS, SBS " << _buckets.size() << " " << _superbuckets.size() << std::endl;

    // populate buckets with values
    UInt current_sum = 0;
    UInt index = 0;
    UInt superbucket_size = _bucket_size * _bucket_size;
    BitVector::const_iterator bit_vec_it = this->_bit_vector.begin();
    for ( ; bit_vec_it != this->_bit_vector.end(); bit_vec_it++, index++) {

        current_sum += *bit_vec_it;
        
        // if we are exiting a bucket, store the result
        if (index % _bucket_size == (_bucket_size - 1)) {

            // indexes of bucket and superbucket for current index
            UInt bucket_index = index / _bucket_size + 1;
            UInt superbucket_index = bucket_index / _bucket_size;

            // if we are exiting superbucket, also update that
            if (index % superbucket_size == (superbucket_size - 1)) {
                _superbuckets[superbucket_index] = current_sum;
            }

            // update the bucket relative to the current superbucket
            this->_buckets[bucket_index] = current_sum -
                this->_superbuckets[superbucket_index];
        }
        
    }

    /*
    std::cout << "Superbucksets" << std::endl;
    for (std::size_t i = 0; i < _superbuckets.size(); i++)
        std::cout << _superbuckets[i] << " ";
    std::cout << std::endl;
    
    std::cout << "Buckets" << std::endl;
    for (std::size_t i = 0; i < _buckets.size(); i++)
        std::cout << _buckets[i] << " ";
    std::cout << std::endl;
    */
}

UInt BitStringRank::rank(UInt i) {
    //std::cout << "BitStringRank rank " << i << ", length " << this->_length << std::endl;
    assert(i <= this->_length);

    if (i == 0) return 0;

    UInt bucket_index = i / this->_bucket_size;
    UInt superbucket_index = bucket_index / this->_bucket_size;

    UInt startIndex = bucket_index * this->_bucket_size;
    UInt sum = 0;
    for (std::size_t ind = startIndex; ind < i; ind++)
    {
        sum += this->_bit_vector[ind];
    }

    return sum + this->_buckets[bucket_index] + 
        this->_superbuckets[superbucket_index];
}
