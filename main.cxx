#include <cstring>
#include <iostream>

#include "res.hpp"

int main() {
    try {
	res::Res r;

	auto len   = r.Len();
	auto total = 0;

	// "next" will be set to the expected next read size, bsz is the
	// maximum size of the decompressed block.
	auto bsz = r.MaxBlockSize();

	// We can assume block max size doesn't change since we encoded
	// the resource in a single pass.
	char into[bsz];

	bool done = false;

	while (!done && total < len) {
	    // count is the number of bytes actually consumed into
	    // "into".  Read up to one full block (bsz.)
	    auto count = r.Read(into, bsz);
	    if (count == 0) {
		// We finished reading.  I'd be surprised if we ever hit
		// this.
		done = true;
	    }

	    total += count;
	    fwrite(into, sizeof(char), count, stdout);
	}
    } catch (const char* s) {
	std::cout << "Exception: " << s << std::endl;
	return 1;
    }

    fflush(stdout);
    return 0;
}
