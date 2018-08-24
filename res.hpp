#include <cstddef>

#include "lz4frame.h"

namespace res {
    class Res {
    public:
        Res() noexcept(true);
	~Res() noexcept(false);
	// Len returns the required size for the target buffer.
        size_t Len() noexcept(true);

	// Read ingests up to len bytes into the target buffer.  If the
	// user passes a NULL target, the Res will create an internally-
	// managed buffer to store the decompressed resource, which will
	// be automatically deleted when the Res is destroyed.
	//
	// If the user passes a buffer with sufficient size, the
	// returned buffer is the one which was passed in.
	// 
	// If the user passes a buffer with insufficient size, the
	// behavior is undefined.
	const char* Read(char* into, size_t len) noexcept(true);

    private:
	 // TODO: lz4.h streaming. LZ4F_dctx* context;
	 std::unique_ptr<char> internal_buffer;

	 static const unsigned char buf[];
	 static const size_t b_comp_len;
    };

    // TODO: lz4.h streaming. size_t lookup_block_size(LZ4F_blockSizeID_t);
};