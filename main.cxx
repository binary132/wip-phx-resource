#include <cstring>
#include <iostream>

#include "res.hpp"

int main() {
    try {
	res::Res r;

	auto len   = r.Len();
	auto total = 0;

	// Allocate full buffer.
	// char     into[len];

	while (total < len) {
	    // Allocate partial buffer.
	    size_t next = 0;
	    auto   bsz  = r.BlockSize(next);
	    char   into[bsz];

	    // memset(into, 0, len);

	    auto count = 0;

	    // count is the number of bytes actually consumed.
	    count = r.Read(into, bsz - count);
	    total += count;

	    fwrite(into, sizeof(char), count, stdout);
	}

	fflush(stdout);
    } catch (const char* s) {
	std::cout << "Exception: " << s << std::endl;
	return 1;
    }

    return 0;
}
