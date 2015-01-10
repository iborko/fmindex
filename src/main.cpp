#include <iostream>
#include <string>

#include "../include/StringRotator.h"
#include "../include/BWTransform.h"
#include "../include/PrefixSumTable.h"
#include "../include/OccurrenceTable.h"
#include "../include/WaveletTree.h"
#include "../include/SuffixArray.h"
#include "../include/test/TestHelper.h"

int main() {
    std::string my = "AGATTAT$";
    char chars[] = {'$','A', 'G', 'T'};
    std::vector<int> alph (chars, chars + sizeof(chars) / sizeof(char) );

    std::string bwt = BWTransform::transform(my);
    std::cout << "Original :" << my << std::endl;
    std::cout << "Transformed :" << bwt << std::endl;

    PrefixSumTableInterface* ps_table = new PrefixSumTable(bwt);
    OccurrenceTableInterface* occ_table = new OccurrenceTable(bwt);
    std::string orig = BWTransform::reverse(bwt, *occ_table, *ps_table);
    std::cout << "Reversed :" << orig << std::endl;

    //test search
    int * sa = SuffixArray::get_sa(my, strlen(my.c_str()));
    std::vector<int> occ_indices = BWTransform::search("GA", alph, sa, *occ_table, *ps_table);

    std::cout << "Search done, pattern indices = ";

    for (std::vector<int>::iterator it = occ_indices.begin() ; it != occ_indices.end(); ++it)
         std::cout << ' ' << *it;
    std::cout << std::endl;
    
    // test occurence tables
    OccurrenceTableInterface *occ_table1 = new WaveletTree(bwt, 4);
    int rank1 = occ_table->get_occ('A', 4);
    int rank2 = occ_table1->get_occ('A', 4);
    std::cout << "Res " << rank1 << " " << rank2 << std::endl;

    rank1 = occ_table->get_occ('T', 5);
    rank2 = occ_table->get_occ('T', 5);
    std::cout << "Res " << rank1 << " " << rank2 << std::endl;
    
    delete occ_table;
    delete occ_table1;
    
    std::string s = "GDCGCDGGFAFBGBFAADADFFDCCABGDACDBFCDGBCCAGDEFAEGDFCGBDB";
    OccurrenceTableInterface *occ_wavelet = new WaveletTree(s, 5);
    delete occ_wavelet;
    
    std::string s1 = "CDGGA";
    occ_wavelet = new WaveletTree(s1, 2);
    std::cout << "Occurence of G up to position 1 " << occ_wavelet->get_occ('G', 1) << std::endl;
    delete occ_wavelet;
    
    const std::string alph1 = "ABCD";
    std::string rand_str = generate_random_string(alph1, 50);
    std::cout << "Random string " << rand_str << std::endl;

    return 0;
}
