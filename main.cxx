#include <cstring>
#include <iostream>

#include "res.hpp"

int main() {
    try {
	res::Res r;

	auto   len   = r.Len();
	auto   total = 0;
	size_t next  = 0;

	// "next" will be set to the expected next read size, bsz is the
	// maximum size of the decompressed block.
	auto bsz = r.MaxBlockSize(next);

	// We can assume block max size doesn't change since we encoded
	// the resource in a single pass.
	char into[bsz];

	while (next != 0 && total < len) {
	    // count is the number of bytes actually consumed into
	    // "into".  It should always match "next".
	    auto count = r.Read(into, next);
	    if (count != next) {
		// Something went wrong?
		throw "weird";
	    }

	    total += count;
	    fwrite(into, sizeof(char), next, stdout);

	    // Get size of the next block.
	    r.MaxBlockSize(next);
	}
    } catch (const char* s) {
	std::cout << "Exception: " << s << std::endl;
	return 1;
    }

    fflush(stdout);
    return 0;
}
