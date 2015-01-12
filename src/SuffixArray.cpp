#include "../include/SuffixArray.h"

IntVector SuffixArray::get_sa(const std::string& s)
{
    size_t n = s.size();
    int* SA = (int *)malloc(n * sizeof(int));
    const unsigned char * STR = reinterpret_cast<const unsigned char *> (s.c_str());

    if(sais(STR, SA, n) != 0) {
        std::cerr << "Failure at sais, SuffixArray generation" << std::endl;
        exit(EXIT_FAILURE);
    }

    return IntVector(SA, SA+n);
}

std::string SuffixArray::bwt(const std::string& s) {

    size_t n = s.size();
    int* A = (int *)malloc(n * sizeof(int));
    unsigned char* T = (unsigned char*)malloc(n * sizeof(unsigned char));
    const unsigned char * STR = reinterpret_cast<const unsigned char *> (s.c_str());

    if(sais_bwt(STR, T, A, n) < 0) {
        std::cerr << "Failure at sais, SA based BW tranformation" << std::endl;
        exit(EXIT_FAILURE);
    }

    return std::string(T, T+n);
}
