#include <string>
#include <cstdlib>
#include "../BitStringRank.h"
#include "../catch/single_include/catch.hpp"

// generates random bool vector
BitVector generate_random_bits(int len) {

    BitVector bit_vector;
    bit_vector.resize(len, 0);
    for (int i = 0; i < len; i++) {
        bit_vector[i] = rand() % 2;
    }

    return bit_vector;
}

// count bits set to 1 up to position pos (not included)
UInt trivial_rank(const BitVector& bit_vector, UInt pos) {
    UInt counter = 0;
    for (size_t i = 0; i < bit_vector.size() && i < pos; i++)
        if (bit_vector[i] == 1) counter++;

    return counter;
}

TEST_CASE("basic bit string rank test", "[BitStringRank]") {
    bool bits[] = {0, 1, 1, 0, 1, 1, 1, 0, 1, 0};
    BitVector bit_vector(bits, bits+10);
    
    BitStringRank *bs_rank = new BitStringRank(bit_vector, 2);
    
    REQUIRE(bs_rank->rank(0) == 0);
    REQUIRE(bs_rank->rank(1) == 0);
    REQUIRE(bs_rank->rank(2) == 1);
    REQUIRE(bs_rank->rank(3) == 2);
    REQUIRE(bs_rank->rank(4) == 2);
    REQUIRE(bs_rank->rank(5) == 3);
    REQUIRE(bs_rank->rank(6) == 4);
    REQUIRE(bs_rank->rank(7) == 5);
    REQUIRE(bs_rank->rank(8) == 5);
    REQUIRE(bs_rank->rank(9) == 6);

    delete bs_rank;
}

TEST_CASE("random bitstrings, lengths in [200, 250] interval", "[BitStringRank]") {

    for (int length = 200; length <= 250; length++) {
        BitVector bit_vector = generate_random_bits(length);

        BitStringRank *bs_rank = new BitStringRank(bit_vector, 6);
        
        // check every rank
        for (int i = 0; i <= length; i++) {
            REQUIRE(bs_rank->rank(i) == trivial_rank(bit_vector, i));
        }

        delete bs_rank;
    }
}
