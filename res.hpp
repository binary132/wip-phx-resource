#include <cstddef>
#include <memory>

#include "lz4frame.h"

namespace res {
    class Res {
    public:
	// Len returns the required size for the target buffer.
	size_t Len() noexcept(true);

	Res() noexcept(false);
	~Res() noexcept(false);

	// MaxBlockSize returns the ideal size of a block which may be
	// consumed by a partial Read.  Read will fill as much as is
	// given, but the performance is best if the full Len() is
	// allocated, or if blocks of MaxBlockSize are used.
	//
	// If a size_t is passed, MaxBlockSize sets its value to the
	// next buffer size to pass to Read.  If this size is 0, the
	// Res is done reading.
	const size_t MaxBlockSize() noexcept(false);
	const size_t MaxBlockSize(size_t&) noexcept(false);

	// Read ingests up to len bytes into the target buffer.  The
	// user may pass a buffer smaller than the full decompressed
	// size returned by Len(), and may make multiple calls to Read
	// to keep filling the user's buffer from the decoded resource.
	//
	// Reset() may be called to begin from the beginning.
	const size_t Read(char* into, size_t len) noexcept(false);

	// Reset returns the state of the Res to its initial position,
	// ready to begin filling a new target buffer.
	void Reset() noexcept(true);

    private:
	LZ4F_dctx* decoder;
	size_t     consumed;

	static const unsigned char buf[];
	static const size_t        b_comp_len;

	const size_t lookupBlkSize(LZ4F_blockSizeID_t) noexcept(true);
    };
}; // namespace res
