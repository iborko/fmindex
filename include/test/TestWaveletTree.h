#include <string>
#include "TestHelper.h"  // generate_random_string(alph, len)
#include "../WaveletTree.h"
#include "../OccurrenceTable.h"
#include "../catch/single_include/catch.hpp"


TEST_CASE("wavelet tree, random strings", "[WaveletTree]") {
    static const std::string alphabet = "ABCDEFGHIJ";

    SECTION("string length 100") {
        std::string s = generate_random_string(alphabet, 100);
        OccurrenceTableInterface *occ_trivial = new OccurrenceTable(s);
        OccurrenceTableInterface *occ_wavelet = new WaveletTree(s, 5);

        for (int i = 0; i < (int)sizeof(alphabet) - 1; i++) {
            for (size_t j = 0; j < s.size(); j++) {
                INFO("Letter " << alphabet[i]);
                INFO("String " << s);
                INFO("Occurences up to position  " << j);
                REQUIRE(occ_trivial->get_occ(alphabet[i], j) ==
                    occ_wavelet->get_occ(alphabet[i], j));
            }
        }
        
        delete occ_trivial;
        delete occ_wavelet;
    }

    SECTION("string length 1000") {
        std::string s = generate_random_string(alphabet, 1000);
        OccurrenceTableInterface *occ_trivial = new OccurrenceTable(s);
        OccurrenceTableInterface *occ_wavelet = new WaveletTree(s, 10);

        for (int i = 0; i < (int)sizeof(alphabet) - 1; i++) {
            for (size_t j = 0; j < s.size(); j++) {
                INFO("Letter " << alphabet[i]);
                INFO("String " << s);
                INFO("Occurences up to position " << j);
                REQUIRE(occ_trivial->get_occ(alphabet[i], j) ==
                    occ_wavelet->get_occ(alphabet[i], j));
            }
        }
        
        delete occ_trivial;
        delete occ_wavelet;
    }
}
