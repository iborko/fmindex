#include "../include/FastaReader.h"

FastaReader::FastaReader(const char* path) 
    : file_(path) {

    if (!file_.is_open()) {
        std::cerr << "Unable to open file: " << path << std::endl;
        exit(EXIT_FAILURE);
    }
}
    
bool FastaReader::is_header(const std::string& s) {
    if (s[0] == ';' || s[0] == '>')
        return true;
    return false;
}

std::auto_ptr<FastaSequence> FastaReader::next() {

    bool readingHeader = 1;
    std::auto_ptr<FastaSequence> fs(new FastaSequence());    

    while(true) {
        // check that last read line is valid
        if (line_.size() > 1 && line_[0] != ' ') {
            if (!readingHeader && is_header(line_))
                return fs;
            
            if (readingHeader && is_header(line_)) {
                fs->name_ += line_.substr(1);
            }
            else {
                fs->sequence_ += line_;
                readingHeader = 0;
            }
        }
        
        // can't read further
        if (!getline(file_, line_)) break;
    }

    // if we read something, return it
    // otherwise return NULL
    if (fs->sequence().size() > 0)
        return fs;
    return std::auto_ptr<FastaSequence>(NULL);
}
