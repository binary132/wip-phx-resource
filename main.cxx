#include <iostream>

#include "res.hpp"

int main() {
    try {
	res::Res r;
	auto     len = r.Len();
	char     into[len];
	auto     out = r.Read(into, len);
	std::cout << "Decoded successfully:" << std::endl
	          << out << std::endl;
    } catch (const char* s) {
	std::cout << "Exception: " << s << std::endl;
	return 1;
    }

    return 0;
}
