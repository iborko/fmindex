#include <iostream>
#include <string>

#include "../include/StringRotator.h"
#include "../include/BWTransform.h"
#include "../include/PrefixSumTable.h"
#include "../include/OccurrenceTable.h"
#include "../include/WaveletTree.h"

int main() {
    std::string my = "AGATTAT$";

    std::string bwt = BWTransform::transform(my);
    std::cout << "Original :" << my << std::endl;
    std::cout << "Transformed :" << bwt << std::endl;

    int * sa = SuffixArray::get_sa(my, strlen(my.c_str()));

    PrefixSumTableInterface* ps_table = new PrefixSumTable(bwt);
    OccurrenceTableInterface* occ_table = new OccurrenceTable(bwt);
    std::string orig = BWTransform::reverse(bwt, *occ_table, *ps_table);
    std::cout << "Reversed :" << orig << std::endl;

    // test occurence tables
    OccurrenceTableInterface *occ_table1 = new WaveletTree(bwt, 4);
    int rank1 = occ_table->get_occ('A', 4);
    int rank2 = occ_table1->get_occ('A', 4);
    std::cout << "Res " << rank1 << " " << rank2 << std::endl;

    rank1 = occ_table->get_occ('T', 5);
    rank2 = occ_table->get_occ('T', 5);
    std::cout << "Res " << rank1 << " " << rank2 << std::endl;

    return 0;
}
