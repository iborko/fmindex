#include "../include/BWTransform.h"

std::string BWTransform::transform(const std::string& s) {
    std::vector<StringRotator*> v;
    v.reserve(s.size());

    for (size_t i = 0; i < s.size(); i++) {
        v.push_back(new StringRotator(s));
        v[i]->rotate(i);
    }

    std::sort(v.begin(), v.end(), ValueComparer<StringRotator>());

    std::string result;
    for (size_t i = 0; i < v.size(); i++) {
        result.push_back(v[i]->get_last_char());
        delete v[i];
    }

    return result;
}
