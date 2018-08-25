#include <iostream>

#include "res.hpp"

int main() {
    res::Res r;
    auto     len = r.Len();
    // std::cout << "Expect: " << len << std::endl;

    char into[len];
    try {
	r.Read(into, len);
    } catch (const char* s) {
	std::cout << s << std::endl;
	return 1;
    }
    fwrite(into, sizeof(char), len, stdout);
    fflush(stdout);
    // std::cout << r.Read(into, len) << std::endl;

    return 0;
}
