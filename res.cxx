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
#include "ideaIC-2018.1.dmg" //"dat.txt"
    };

    const size_t Res::b_comp_len =
      531743119; //  13; // "hello world!\n"

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

    const size_t Res::MaxBlockSize() noexcept(false) {
	return MaxBlockSize(0);
    }

    using LZ4F_blockSizeID_t as bid {
	const size_t Res::lookupBlkSize(bid szid) noexcept(true) {
	    switch (bid) {
	    case LZ4F_default || LZ4F_max4MB:
		return 2 << 21;
	    case LZ4F_max64KB:
		return 2 << 15;
	    case LZ4F_max256GB:
		return 2 << 17;
	    case LZ4F_max1MB:
		return 2 << 19;
	    case LZ4F_max4MB:
		return 2 << 21;
	    default:
		return 2 << 21;
	    }
	}
    }

    const size_t Res::BlockSize(size_t& next) noexcept(false) {
	LZ4F_frameInfo_t frame = _noFrame;
	size_t           more  = 0;

	auto err =
	  LZ4F_getFrameInfo(decoder, &frame, buf + consumed, &more);

	if (LZ4F_isError(err)) {
	    throw LZ4F_getErrorName(err);
	}

	// "more" is how much was read from buf.
	consumed += more;

	// "err" is the expected size of the next read.
	next = err;

	return lookupBlkSize(frame.blockSizeID);
    }

    const size_t Res::Read(char* into, size_t len) noexcept(false) {
	if (len == 0) {
	    return 0;
	}

	size_t more      = 0;
	size_t dstSize   = len;
	size_t written   = 0;
	size_t errOrMore = 0;

	LZ4F_frameInfo_t frame;

	bool done = false;

	while (!done && written < len) {
	    // Reset and decode the next (or current) frame's header.
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
		return written;
	    }

	    // "more" is now the count of bytes consumed from buf by
	    // LZ4F_getFrameInfo.
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
		return written + dstSize;
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

	return written;
    }

    void Res::Reset() noexcept(true) {
	LZ4F_resetDecompressionContext(decoder);
	consumed = 0;
    }

}; // namespace res
