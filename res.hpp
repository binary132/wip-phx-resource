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

	// Read ingests up to len bytes into the target buffer.  If
	// the user passes a NULL target, the Res will create an
	// internally- managed buffer to store the decompressed
	// resource, which will be automatically deleted when the Res
	// is destroyed.
	//
	// If the user passes a buffer with sufficient size, the
	// returned buffer is the one which was passed in.
	//
	// If the user passes a buffer with insufficient size, the
	// behavior is undefined.
	const char* Read(char* into, size_t len) noexcept(false);

    private:
	LZ4F_dctx*            decoder;
	std::unique_ptr<char> internal_buffer;

	static const unsigned char buf[];
	static const size_t        b_comp_len;
    };
}; // namespace res
