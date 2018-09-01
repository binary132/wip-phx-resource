#include <iostream>

#include "mapper.hpp"
#include "resource.hpp"

using res::ID;
using res::Mapper;

int main() {
    try {
	auto r = Mapper::Fetch(ID::dat_txt);

	auto len   = r->Len();
	auto total = 0;

	// "next" will be set to the expected next read size, bsz is the
	// maximum size of the decompressed block.
	auto bsz = r->BlockSize();

	// We can assume block max size doesn't change since we encoded
	// the resource in a single pass.
	char into[bsz];

	bool done = false;

	while (!done && total < len) {
	    // count is the number of bytes actually consumed into
	    // "into".  Read up to one full block (bsz.)
	    auto count = r->Read(into, bsz);
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
