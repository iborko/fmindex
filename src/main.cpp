#include <iostream>
#include <string>

#include "../include/StringRotator.h"
#include "../include/BWTransform.h"

int main() {
    std::string my = "AGATTAT$";

    std::string bwt = BWTransform::transform(my);
    std::cout << "Original :" << my << std::endl;
    std::cout << "Transformed :" << bwt << std::endl;

    return 0;
}
