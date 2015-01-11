#ifndef FASTQ_READER_H_
#define FASTQ_READER_H_

#include <string>
#include <fstream>
#include <memory>
#include <iostream>
#include <cstdlib>
#include "FastaReader.h" // FastaSequence

// reads sequences in FASTQ format
// NOTE: reads only sequence and description, other FASTQ data is ignored
class FastqReader {
public:
    FastqReader(const char* path);
    std::auto_ptr<FastaSequence> next();

private:
    std::ifstream file_;
    void invalid_format(const std::string&);
};

#endif
