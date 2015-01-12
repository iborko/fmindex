#ifndef FASTA_READER_H_
#define FASTA_READER_H_

#include <string>
#include <fstream>
#include <memory>
#include <iostream>
#include <cstdlib>

class FastSequenceInterface {
public:
    virtual ~FastSequenceInterface() { }
    
    virtual std::string& name() = 0;
    virtual std::string& sequence() = 0;
};

class FastaReader;
class FastqReader;

// contains one fasta sequence
class FastaSequence : public FastSequenceInterface {
public:
    virtual ~FastaSequence() { }
    
    // description line for fasta format
    virtual std::string& name() { return name_; }
    // genetic sequence
    virtual std::string& sequence() { return sequence_; }
    
private:
    FastaSequence() { } // only Fasta reader can create it
    std::string name_;
    std::string sequence_;

friend class FastaReader;
friend class FastqReader;
};

// reads sequences in FASTA format
class FastaReader {
public:
    FastaReader(const char* path);
    
    // fetch next fasta sequence from file
    std::auto_ptr<FastaSequence> next();

private:
    std::ifstream file_;
    std::string line_;
    bool is_header(const std::string& s);
};

#endif
