#include <istream>
#include <sstream>
#include <string>
#include <memory>
#include <cstddef>
#include <exception>

#include "lz4.h"

#include "res.hpp"

namespace res {
    class exc1 : std::exception {};
    class exc2 : std::exception {};
/* TODO: lz4.h
    size_t lookup_block_size(LZ4F_blockSizeID_t szid) {
	size_t bsz = 0;

	switch (szid) {
        case LZ4F_default:
	    bsz = -1
        case LZ4F_max64KB:
	    bsz = 2 << 15;
        case LZ4F_max256KB:
	    bsz = 2 << 17;
        case LZ4F_max1MB:
	    bsz = 2 << 19;
	case LZ4F_max4MB:
	    bsz = 2 << 21;
        };

	return bsz;
    }
*/
    // TODO: Generate these constants in the phx tool.
    const unsigned char Res::buf[] = {
0x68,0x65,0x6c,0x6c,0x6f,0x0a, // |hello.|
    };
 
    const size_t b_comp_len = 0;

    Res::Res() noexcept(false): context(NULL) {
        /* TODO: lz4.h streaming.
	auto lz_ver = LZ4F_getVersion();
	auto err = LZ4F_createDecompressionContext(&context, lz_ver);
	if (LZ4F_isError(err)) {
	    throw LZ4F_getErrorName(err);
	}
        */
    }

    Res::~Res() noexcept(false) {
	 /* TODO: lz4.h streaming.
	auto err = LZ4F_freeDecompressionContext(&context);
	if (LZ4F_isError(err)) {
	    // TODO: Should never happen.
	    throw LZ4F_getErrorName(err);
	}
	*/
    }

    size_t Res::Len() noexcept(true) {
	 return b_comp_len;
    }

    const char* Res::Read(char* into, size_t len) noexcept(true) {
	// Decode first LZ4 block header.

	/* TODO: lz4.h streaming.
	auto lzhdr = LZ4F_frameInfo_t{0};
	auto err = LZ4F_getFrameInfo(context, &lzhdr, buf, &hdrLen);
	if (LZ4_isError(err)) {
	    // TODO: Should never happen.
     	    throw LZ4F_getErrorName(err);
	}
        auto bsz = lookup_block_size(lzhdr.blockSizeID);
	if (bsz == -1) {
            // TODO: Should never happen.
	    printf("wrong block size: %d\n", lzhdr.blockSizeID);
	    throw NULL;
	}

	char tmp_buf[bsz];

	if (!into) {
	    // Allocate internal buffer for the user.
	    internal_buffer = std::unique_ptr<char>(new char(len));
	    into = internal_buffer.get();
	}

	auto done = false;
	auto offset = 0;
	while (!done) {
	    size_t got = bsz;
	    size_t get = b_comp_len-total;
            // Decode each block until done, first copying into the
	    // frame buffer, then into the target.
	    auto blkSize = LZ4F_decompress(context,
					   tmp_buf, &got,
					   buf+offset, &get,
					   lzhdr.
		 );
	    if (total + got >= len) {
                // We're done.
		done = true;
	    }
	    memcpy(into, tmp_buf, got);
	    offset += 
	}
	
	*/
	return into;
    }
};
