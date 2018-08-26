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
    namespace {
	static const LZ4F_frameInfo_t _noFrame{};
    };

    // TODO: Generate these constants in the phx tool.
    const unsigned char Res::buf[] = {
#include "dat.txt"
    };

    const size_t Res::b_comp_len = 13; // "hello world!\n"

    size_t Res::Len() noexcept(true) { return b_comp_len; }

    Res::Res() noexcept(false) {
	auto err =
	  LZ4F_createDecompressionContext(&decoder, LZ4F_getVersion());
	if (LZ4F_isError(err)) {
	    throw LZ4F_getErrorName(err);
	}
    }

    Res::~Res() noexcept(false) {
	auto err = LZ4F_freeDecompressionContext(decoder);
	if (LZ4F_isError(err)) {
	    throw LZ4F_getErrorName(err);
	}
    }

    const char* Res::Read(char* into, size_t len) noexcept(false) {
	size_t more      = std::extent<decltype(buf)>::value;
	size_t dstSize   = len;
	size_t written   = 0;
	size_t errOrMore = 0;
	size_t consumed  = 0;

	LZ4F_frameInfo_t frame;

	bool done = false;

	while (!done) {
	    // Reset and decode the next frame's header.
	    frame = _noFrame;
	    more  = LZ4F_HEADER_SIZE_MAX;

	    errOrMore =
	      LZ4F_getFrameInfo(decoder, &frame, buf + consumed, &more);
	    if (LZ4F_isError(more)) {
		throw LZ4F_getErrorName(more);
	    }
	    if (errOrMore == 0) {
		// When the next block is 0-sized, we're done.

		// TODO: maybe check decoder state?  But it should just
		// always work.
		return into;
	    }

	    // "more" is now the count of bytes consumed from buf.
	    consumed += more;

	    // "errOrMore" is now the size of the block+header expected
	    // by LZ4F_decompress as "srcSizePtr", to control the number
	    // of bytes	consumed.
	    more = errOrMore;

	    // Consume the frame into the destination.
	    errOrMore =
	      LZ4F_decompress(decoder, into + written, &dstSize,
	                      buf + consumed, &more, NULL);
	    if (LZ4F_isError(errOrMore)) {
		throw LZ4F_getErrorName(errOrMore);
	    }
	    if (errOrMore == 0) {
		// When the header is 0-sized, we're done.
		// TODO: This should never happen, double-check.
		return into;
	    }

	    // After decoding the block, "more" is the count of bytes
	    // consumed, in that call, from the internal compressed
	    // buffer source.  Add this to the total offset.
	    consumed += more;

	    // dstSize is now the number of bytes written, by this call,
	    // into the output buffer "into".  Add it to the total.
	    written += dstSize;

	    // Store the remaining size of the output buffer "into" in
	    // dstSize for the next call to LZ4F_decompress.
	    dstSize = len - written;
	}

	return into;
    }

}; // namespace res
