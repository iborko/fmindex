#include "../include/WaveletTree.h"

WaveletTree::WaveletTree(const std::string& s, UInt bucket_size)
    : bucket_size_(bucket_size) {

    // construct string alphabet
    CharSet chars(s.c_str(), s.c_str() + s.size());
    std::string alph = "";
    CharSet::const_iterator charset_it = chars.begin();
    for (; charset_it != chars.end(); charset_it++) {
        alph += *charset_it;
    }

    // get char counts in the string s
    CharIntMap counts;
    std::string::const_iterator string_it = alph.begin();
    for (; string_it != alph.end(); string_it++)
        counts[*string_it] = 0;

    string_it = s.begin();
    for (; string_it != s.end(); string_it++)
        counts[*string_it] += 1;

    std::string* temp = new std::string(s);
    this->root_ = this->create_node(temp, alph, counts);
}

WaveletTree::~WaveletTree() {
    delete this->root_;
}

char WaveletTree::calc_pivot(const std::string& alph, const CharIntMap& counts) {

    UIntVector scores;
    scores.resize(alph.size(), 0);

    for (std::size_t i = 0; i < alph.size(); i++) {

        // calc the number of 0s and 1s
        UInt sum_before = 0;
        UInt sum_after = 0;
        for (std::size_t j = 0; j < i; j++) {
            // operator[] can't be used in const map, so I had to use
            // find to get iterator
            CharIntMap::const_iterator elem = counts.find(alph[j]);
            if (elem == counts.end())
                throw std::runtime_error("counts has missing key");
            sum_before += elem->second;
        }
        for (std::size_t j = i; j < alph.size(); j++) {
            CharIntMap::const_iterator elem = counts.find(alph[j]);
            if (elem == counts.end())
                throw std::runtime_error("counts has missing key");
            sum_after += elem->second;
        }

        // diff between numbers of 0s and 1s
        scores[i] = abs(sum_before - sum_after);
        
        // if current score is worse than prev, than prev is the best,
        // continuing will only give worse scores
        if (i > 0 && scores[i] > scores[i-1])
            return alph[i-1];
    }

    return alph[alph.size() - 1];
}

WaveletTree::Node* WaveletTree::create_node(std::string* str,
    const std::string& alph, const CharIntMap& counts) {
    
    if (alph.size() < 2) {
        delete str;
        return NULL;
    }

    std::size_t str_len = str->size();
    /*
    std::cout << "--- Creating new node" << std::endl;
    std::cout << "-string is: " << *str << std::endl;
    std::cout << "-str_len is: " << str_len << std::endl;
    std::cout << "-alphab is: " << alph << std::endl;
    */

    // optimal pivot for this node
    char pivot = this->calc_pivot(alph, counts);
    //std::cout << "Selected pivot is " << pivot << std::endl;

    // create the bitstring
    BitVector bit_string;
    bit_string.resize(str->size());
    for (std::size_t i = 0; i < str_len; i++)
        bit_string[i] = str->at(i) > pivot;

    /*
    std::cout << "BitString" << std::endl;
    for (std::size_t i = 0; i < bit_string.size(); i++)
        std::cout << bit_string[i] << " ";
    std::cout << std::endl;
    */

    Node* node = new Node(bit_string, this->bucket_size_);
    node->pivot = pivot;

    // fill with spaces, create string with proper size
    std::string* left_string = new std::string(node->bit_string.rank(str_len-1),
        ' ');
    std::string* right_string = new std::string(str_len - left_string->size(),
        ' ');

    // populate strins for each node with appropriate values
    UInt left_index = 0;
    UInt right_index = 0;
    for (std::size_t i = 0; i < str_len; i++) {
        if (str->at(i) >= pivot) {
            (*right_string)[right_index] = str->at(i);
            right_index++;
        }
        else {
            (*left_string)[left_index] = str->at(i);
            left_index++;
        }
    }
    //std::cout << "L: " << *left_string << ", R: " << *right_string << std::endl;

    delete str;

    std::size_t pivot_index = alph.find(pivot);
    std::string left_alph = alph.substr(0, pivot_index);
    std::string right_alph = alph.substr(pivot_index, std::string::npos);

    node->left_node = this->create_node(left_string, left_alph, counts);
    node->right_node = this->create_node(right_string, right_alph, counts);

    return node;
}

int WaveletTree::get_occ(char c, int p) const {
    
    Node* node = this->root_;

    int rank = p;
    while (node != NULL && rank != 0) {

        // rank in th bitstring for this node
        int rank_prev = rank;
        rank = node->bit_string.rank(rank_prev);

        if (c < node->pivot) {
            // we need the count of zeros
            rank = rank_prev - rank;
            //std::cout << "Rank in node (left)" << node->pivot << " = " << rank << std::endl;
            node = node->left_node;
        }
        else {
            //std::cout << "Rank in node (right)" << node->pivot << " = " << rank << std::endl;
            node = node->right_node;
        }
    }

    return rank;
}
