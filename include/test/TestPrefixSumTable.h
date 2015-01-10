#include <string>
#include "TestHelper.h"  // generate_random_string(alph, len)
#include "../PrefixSumTable.h"
#include "../catch/single_include/catch.hpp"

// count chars smaller than c in string s
int count_smaller_chars(const std::string &s, char c) {
    int sum = 0;
    for (size_t i = 0; i < s.size(); i++)
        if (s[i] < c) sum++;

    return sum;
}

TEST_CASE("prefix sum table", "[PrefixSumTable]") {
    static const std::string alphabet = "ACGT";

    SECTION("request prefix sum of nonexisting character") {
        std::string s = generate_random_string(alphabet, 10);
        PrefixSumTableInterface *ps_table = new PrefixSumTable(s);

        REQUIRE(ps_table->get_C('Z') == 0);
        
        delete ps_table;
    }

    SECTION("string length 10") {
        std::string s = "ATTGACATTG";
        PrefixSumTableInterface *ps_table = new PrefixSumTable(s);

        REQUIRE(ps_table->get_C('A') == 0);
        REQUIRE(ps_table->get_C('C') == 3);
        REQUIRE(ps_table->get_C('G') == 4);
        REQUIRE(ps_table->get_C('T') == 6);
        
        delete ps_table;
    }

    SECTION("string length 100") {
        std::string s = generate_random_string(alphabet, 100);
        PrefixSumTableInterface *ps_table = new PrefixSumTable(s);

        REQUIRE(ps_table->get_C('A') == count_smaller_chars(s, 'A')); 
        REQUIRE(ps_table->get_C('C') == count_smaller_chars(s, 'C'));
        REQUIRE(ps_table->get_C('G') == count_smaller_chars(s, 'G'));
        REQUIRE(ps_table->get_C('T') == count_smaller_chars(s, 'T'));
        
        delete ps_table;
    }

    SECTION("string length 1000") {
        std::string s = generate_random_string(alphabet, 1000);
        PrefixSumTableInterface *ps_table = new PrefixSumTable(s);

        REQUIRE(ps_table->get_C('A') == count_smaller_chars(s, 'A')); 
        REQUIRE(ps_table->get_C('C') == count_smaller_chars(s, 'C'));
        REQUIRE(ps_table->get_C('G') == count_smaller_chars(s, 'G'));
        REQUIRE(ps_table->get_C('T') == count_smaller_chars(s, 'T'));
        
        delete ps_table;
    }

    SECTION("string length 10000") {
        std::string s = generate_random_string(alphabet, 10000);
        PrefixSumTableInterface *ps_table = new PrefixSumTable(s);

        REQUIRE(ps_table->get_C('A') == count_smaller_chars(s, 'A')); 
        REQUIRE(ps_table->get_C('C') == count_smaller_chars(s, 'C'));
        REQUIRE(ps_table->get_C('G') == count_smaller_chars(s, 'G'));
        REQUIRE(ps_table->get_C('T') == count_smaller_chars(s, 'T'));
        
        delete ps_table;
    }
}
