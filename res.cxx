#include <cstddef>
#include <cstring>
#include <exception>
#include <istream>
#include <memory>
#include <sstream>
#include <string>

#include "lz4frame.h"

#include "res.hpp"

namespace res {
    // TODO: Generate these constants in the phx tool.
    const unsigned char Res::buf[] = {
#include "dat.txt"
    };

    const size_t Res::b_comp_len = 13; // "hello world!\n"

    size_t Res::Len() noexcept(true) {
	// 	return std::extent<decltype(buf)>::value;
	// }
	return b_comp_len;
    }

    const char* Res::Read(char* into, size_t len) noexcept(false) {
	// std::memcpy(into, buf, len);

	// auto err = LZ4_decompress_safe(
	//   reinterpret_cast<const char*>(buf), into, b_comp_len, len);

	// if (err < 0) {
	//     throw "bad stream";
	// }

	return into;
    }

}; // namespace res
