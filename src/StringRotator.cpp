#include "../include/StringRotator.h"

StringRotator::StringRotator(const std::string& s) {
    this->s = s.c_str();
    this->length = s.size();
    this->last = this->s + this->length;
    this->begin = this->s;
    this->end = this->last - 1;
}

StringRotator::StringRotator(const StringRotator& obj) {
    this->s = obj.s;
    this->length = obj.length;
    this->last = obj.last;
    this->begin = obj.begin;
    this->end = obj.end;
}

void StringRotator::rotate() {
    this->begin++;
    this->end++;

    // check if pointers have reached end
    if (this->begin == this->last)
        this->begin = this->s;

    if (this->end == this->last)
        this->end= this->s;
}

std::string StringRotator::get_str() {
    std::string ret;
    const char* curr = this->begin;
    
    while(curr != this->end) {
        ret.push_back(*curr);
        curr++;
        if (curr == this->last)
            curr = this->s;
    }
    ret.push_back(*curr);
    return ret;
}

char StringRotator::get_first_char() {
    return *(this->begin);
}

char StringRotator::get_last_char() {
    return *(this->end);
}

bool StringRotator::operator<(const StringRotator& other) const {
    const char *l = this->begin;
    const char *r = other.begin;
    size_t len = this->length < other.length ? this->length : other.length;

    for (size_t i = 0; i < len; i++) {
        if (*l != *r)
            return *l < *r;
        l++; r++;
        if (l == this->last)
            l = this->s;
        if (r == other.last)
            r = other.s;
    }
    return true;
}
