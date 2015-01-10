#ifndef TEST_HELPER_H_
#define TEST_HELPER_H_

#include <cstdlib>
#include <string>

// generates random string of length len, from alphabet alph
std::string generate_random_string(const std::string &alph, int len) {
    std::string s;
    
    for (int i = 0; i < len; i++)
        s.push_back(alph[rand() % alph.size()]);

    return s;
}

#endif
