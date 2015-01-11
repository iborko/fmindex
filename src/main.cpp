#include <iostream>

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
            "Wrong number of arguments\n"
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

    std::string bw_transformed = BWTransform::transform(fs->sequence());

    OccurrenceTableInterface* occ_table;
    // if wavelet tree implementation is requested
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
    //alphabet_set.insert(fs->sequence().begin(), fs->sequence().end());
    for(size_t i = 0; i < fs->sequence().size(); i++)
        alphabet_set.insert(fs->sequence()[i]);
    std::vector<char> alphabet(alphabet_set.begin(), alphabet_set.end());

    PrefixSumTableInterface* prefixsum_table = new PrefixSumTable(fs->sequence());
    int* suffix_array = SuffixArray::get_sa(fs->sequence(), fs->sequence().size());

    // read sequence reads (FASTQ file format)
    FastqReader reads_reader(argv[2]);
    while (true) {
        std::auto_ptr<FastaSequence> read(reads_reader.next());
        if (read.get() == NULL) break;

        std::cout << "Sequence identifier: " << read->name() << std::endl;
        std::vector<int> indices = search(read->sequence(), alphabet, suffix_array,
            *occ_table, *prefixsum_table);
        
        // print indices
        for (std::vector<int>::iterator it = indices.begin() ; it != indices.end(); ++it)
            std::cout << *it << ' ';
        std::cout << std::endl;
    }

    return 0;
}
