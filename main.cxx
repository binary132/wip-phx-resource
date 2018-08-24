#include <iostream>

#include "res.hpp"

int main() {
    res::Res r;
    auto     len = r.Len();
    std::cout << "Expect: " << len << std::endl;

    char into[len];

    std::cout << r.Read(into, len) << std::endl;

    return 0;
}
