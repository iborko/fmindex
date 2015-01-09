#include <string>
#include <cstdlib>
#include "../PrefixSumTable.h"
#include "../catch/single_include/catch.hpp"

// generates random string of length len, from alphabet alph
std::string generate_random_string(const char* alph, int len) {
    std::string s;
    for (int i = 0; i < len; i++)
        s.push_back(alph[rand() % (sizeof(alph) - 1)]);

    return s;
}

// count chars smaller than c in string s
int count_smaller_chars(const std::string &s, char c) {
    int sum = 0;
    for (size_t i = 0; i < s.size(); i++)
        if (s[i] < c)
            sum++;

    return sum;
}

TEST_CASE("prefix sum table", "[PrefixSumTable]") {
    static const char alphabet[] = 
        "ACGT";

    SECTION("string length 10") {
        std::string s = "ATTGACATTG";
        PrefixSumTableInterface *ps_table = new PrefixSumTable(s);

        REQUIRE(ps_table->get_C('A') == 0); 
        REQUIRE(ps_table->get_C('C') == 3); 
        REQUIRE(ps_table->get_C('G') == 4); 
        REQUIRE(ps_table->get_C('T') == 6); 
    }

    SECTION("string length 100") {
        std::string s = generate_random_string(alphabet, 100);
        PrefixSumTableInterface *ps_table = new PrefixSumTable(s);

        REQUIRE(ps_table->get_C('A') == count_smaller_chars(s, 'A')); 
        REQUIRE(ps_table->get_C('C') == count_smaller_chars(s, 'C'));
        REQUIRE(ps_table->get_C('G') == count_smaller_chars(s, 'G'));
        REQUIRE(ps_table->get_C('T') == count_smaller_chars(s, 'T'));
    }

    SECTION("string length 1000") {
        std::string s = generate_random_string(alphabet, 1000);
        PrefixSumTableInterface *ps_table = new PrefixSumTable(s);

        REQUIRE(ps_table->get_C('A') == count_smaller_chars(s, 'A')); 
        REQUIRE(ps_table->get_C('C') == count_smaller_chars(s, 'C'));
        REQUIRE(ps_table->get_C('G') == count_smaller_chars(s, 'G'));
        REQUIRE(ps_table->get_C('T') == count_smaller_chars(s, 'T'));
    }

    SECTION("string length 10000") {
        std::string s = generate_random_string(alphabet, 10000);
        PrefixSumTableInterface *ps_table = new PrefixSumTable(s);

        REQUIRE(ps_table->get_C('A') == count_smaller_chars(s, 'A')); 
        REQUIRE(ps_table->get_C('C') == count_smaller_chars(s, 'C'));
        REQUIRE(ps_table->get_C('G') == count_smaller_chars(s, 'G'));
        REQUIRE(ps_table->get_C('T') == count_smaller_chars(s, 'T'));
    }
}
