#include "../include/FastqReader.h"

FastqReader::FastqReader(const char* path)
    : file_(path) {

    if (!file_.is_open()) {
        std::cerr << "Unable to open file: " << path << std::endl;
        exit(EXIT_FAILURE);
    }
}

void FastqReader::invalid_format(const std::string& line) {
    std::cerr << "Unsupported FASTQ file format" << std::endl;
    if (line.size() > 0)
        std::cerr << "->line: " << line << std::endl;
    exit(EXIT_FAILURE);
}


std::auto_ptr<FastaSequence> FastqReader::next() {
    
    std::string line;
    std::auto_ptr<FastaSequence> fs(new FastaSequence());

    // read identifier
    if (!getline(file_, line)) {
        // if we can't read idenfitier, there is no more sequences
        return std::auto_ptr<FastaSequence>(NULL);
    }
    if (line.size() < 1 || line[0] != '@') invalid_format(line);
    fs->name_ += line.substr(1);

    // read sequence
    while (getline(file_, line)) {
        if (line[0] == '+') break;

        fs->sequence_ += line;
    }
    
    // read sequence identifiers
    if (line[0] != '+') invalid_format(line);
    // read quality values
    if (!getline(file_, line)) invalid_format(line);

    return fs;
}
