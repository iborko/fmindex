#ifndef STRINGROTATOR_H_
#define STRINGROTATOR_H_

#include <string>
#include <cstring>

class StringRotator {
public:
    StringRotator(const std::string& s);
    void rotate();
    void rotate(unsigned int);
    std::string get_str();
    char get_last_char();
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
