#include <string>
#include "TestHelper.h"  // generate_random_string(alph, len)
#include "../OccurrenceTable.h"
#include "../catch/single_include/catch.hpp"

// count occurrences of character c up to position c
int count_occurrences(const std::string& s, char c, int pos) {
    int occurences = 0;
    for (size_t i = 0; i < s.size() && (int)i < pos; i++ ) {
        if (s[i] == c) occurences++;
    }

    return occurences;
}

TEST_CASE("occurence table", "[OccurenceTable]") {
    static const std::string alphabet = "ACGT";

    SECTION("string length 5") {
        std::string s = "ATTAT";
        OccurrenceTableInterface *occ_table = new OccurrenceTable(s);

        REQUIRE(occ_table->get_occ('A', 0) == 0);
        REQUIRE(occ_table->get_occ('A', 1) == 1);
        REQUIRE(occ_table->get_occ('A', 2) == 1);
        REQUIRE(occ_table->get_occ('A', 3) == 1);
        REQUIRE(occ_table->get_occ('A', 4) == 2);

        REQUIRE(occ_table->get_occ('T', 0) == 0);
        REQUIRE(occ_table->get_occ('T', 1) == 0);
        REQUIRE(occ_table->get_occ('T', 2) == 1);
        REQUIRE(occ_table->get_occ('T', 3) == 2);
        REQUIRE(occ_table->get_occ('T', 4) == 2);
        
        delete occ_table;
    }

    SECTION("string length 1000") {
        std::string s = generate_random_string(alphabet, 1000);
        OccurrenceTableInterface *occ_table = new OccurrenceTable(s);

        for (int i = 0; i < (int)sizeof(alphabet) - 1; i++) {
            for (size_t j = 0; j < s.size(); j++) {
                REQUIRE(occ_table->get_occ(alphabet[i], j) ==
                    count_occurrences(s, alphabet[i], j));
            }
        }
        
        delete occ_table;
    }

    SECTION("request occurence of nonexisting character") {
        std::string s = generate_random_string(alphabet, 10);
        OccurrenceTableInterface *occ_table = new OccurrenceTable(s);

        REQUIRE(occ_table->get_occ('Z', 5) == 0);
        
        delete occ_table;
    }

    SECTION("request occurence of nonexisting position") {
        std::string s = generate_random_string(alphabet, 10);
        OccurrenceTableInterface *occ_table = new OccurrenceTable(s);

        REQUIRE(occ_table->get_occ('A', 20) >= 0);
        
        delete occ_table;
    }
}
