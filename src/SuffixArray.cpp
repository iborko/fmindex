#include "../include/SuffixArray.h"

IntVector SuffixArray::get_sa(const std::string& s, int n)
{
    int* SA = (int *)malloc(n * sizeof(int));

    if(sais((unsigned char*)s.c_str(), SA, n) != 0) {
        std::cerr << "Failure at sais, SuffixArray generation" << std::endl;
        exit(EXIT_FAILURE);
    }

    return IntVector(SA, SA+n);
}
