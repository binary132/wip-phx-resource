#include <cstddef>
#include <cstring>
#include <exception>
#include <istream>
#include <memory>
#include <sstream>
#include <string>

#include "lz4.h"

#include "res.hpp"

namespace res {
    size_t Res::Len() noexcept(true) { return b_comp_len; }

    const char* Res::Read(char* into, size_t len) noexcept(true) {
	auto err = LZ4_decompress_safe(
	  reinterpret_cast<const char*>(buf), into, b_comp_len, len);

	if (err < 0) {
	    throw "bad stream";
	}

	return into;
    }

    // TODO: Generate these constants in the phx tool.
    const unsigned char Res::buf[] = {
#include "dat.txt"
    };

    const size_t Res::b_comp_len = 12;
}; // namespace res
