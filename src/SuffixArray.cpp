
#include "../include/SuffixArray.h"

int * SuffixArray::get_sa(const std::string& s, int n)
{
    unsigned char * T = (unsigned char *) malloc(n * sizeof(unsigned char));
    int * SA = (int *)malloc(n * sizeof(int));

    strcpy( (char*) T, s.c_str());

    if(sais(T, SA, n) != 0) {
      fprintf(stderr, " failure - sais Suffix Array generation\n");
      exit(EXIT_FAILURE);
    }

    return SA;
}
