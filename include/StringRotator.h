#ifndef STRINGROTATOR_H_
#define STRINGROTATOR_H_

#include <string>
#include <cstring>

// string wrapper that allows O(1) string circular rotation and comparation
class StringRotator {
public:
    // construct from std::string
    StringRotator(const std::string& s);
    // copy constructor
    StringRotator(const StringRotator& obj);

    // circular rotation on left by 1
    void rotate();

    // return rotated string
    std::string get_str();
    // return last character of string
    char get_last_char();
    // return first character of string
    char get_first_char();

    bool operator<(const StringRotator& other) const;

private:
    const char* s;
    const char* last;
    const char* begin;
    const char* end;
    size_t length;
};

#endif
