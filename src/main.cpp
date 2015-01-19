// Copyright 2015 iborko
// Distributed under MIT license
// See file LICENSE for detail or copy at
// https://raw.githubusercontent.com/iborko/fmindex/master/LICENSE

#include <iostream>
#include <cassert>

#include "../include/OccurrenceTable.h"
#include "../include/WaveletTree.h"
#include "../include/PrefixSumTable.h"
#include "../include/SuffixArray.h"
#include "../include/FastqReader.h"
#include "../include/BWTransform.h"
#include "../include/FMIndex.h" // search

const int DEFAULT_BUCKET_SIZE = 20;

int main(int argc, char *argv[]) {

    if (argc < 3) {
        std::cerr <<
            "Missing arguments\n"
            "Usage:\n"
            "    fmindex <sequence.fa> <reads.fq> "
            "[<occurence_implementation> [<bucket_size>]]\n"
            "Available occurence implementations: 0 (trivial), 1 (wavelet tree)\n"
            "Example:\n"
            "    fmindex escherichia.fa reads.fq 1 20\n";
        exit(EXIT_FAILURE);
    }
    
    // read whole sequence (FASTA file format)
    FastaReader seq_reader(argv[1]);
    std::auto_ptr<FastaSequence> fs(seq_reader.next());
    if (fs.get() == NULL) {
        std::cerr << "Cant read sequence from " << argv[1] << std::endl;
        exit(EXIT_FAILURE);
    }
    fs->sequence().push_back('$');
    
    size_t sequence_size = fs->sequence().size();
    IntVector suffix_array = SuffixArray::get_sa(fs->sequence());

    // slower bw transformation (rotation-of-string based)
    //std::string bw_transformed = BWTransform::transform(fs->sequence());

    // suffix array based bw transformation
    std::string bw_transformed(sequence_size, '.');
    const std::string& sequence = fs->sequence();
    for (size_t i = 0; i < suffix_array.size(); i++) {
        size_t loc = (suffix_array[i] + sequence_size - 1) % sequence_size;
        bw_transformed[i] = sequence[loc];
    }

    // if wavelet tree implementation is requested
    OccurrenceTableInterface* occ_table;
    if (argc > 3 && strcmp(argv[3], "1") == 0) {

        int bucket_size = DEFAULT_BUCKET_SIZE;
        if (argc > 4) bucket_size = atoi(argv[4]);

        occ_table = new WaveletTree(bw_transformed, bucket_size);
    }
    // otherwise use trivial implementation
    else {
        occ_table = new OccurrenceTable(bw_transformed);
    }

    // build alphabet
    std::set<char> alphabet_set;
    alphabet_set.insert(fs->sequence().begin(), fs->sequence().end());
    std::vector<char> alphabet(alphabet_set.begin(), alphabet_set.end());

    PrefixSumTableInterface* prefixsum_table = new PrefixSumTable(fs->sequence());

    // read sequence reads (FASTQ file format)
    FastqReader reads_reader(argv[2]);
    while (true) {
        std::auto_ptr<FastaSequence> read(reads_reader.next());
        if (read.get() == NULL) break;

        std::cout << read->name() << std::endl;
        std::vector<int> indices = search(read->sequence(), alphabet, suffix_array,
            *occ_table, *prefixsum_table);
        
        // print indices
        for (std::vector<int>::iterator it = indices.begin() ; it != indices.end(); ++it)
            std::cout << *it << ' ';
        std::cout << std::endl;
    }

    return 0;
}
