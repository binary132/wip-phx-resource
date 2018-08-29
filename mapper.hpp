#ifndef PHX_RES_MAPPER
#define PHX_RES_MAPPER

#include <map>

#include "id.hpp"
#include "resource.hpp"

namespace res {
    // Mapper encapsulates implementation details of the mapping of IDs
    // to Resources away from the user.
    //
    // Fetch is used to retrieve a new Resource, which can be used to
    // decompress a static asset.  It does not create a new copy of the
    // asset.
    //
    // TODO: Parameterize Mapper to allow using debug-mode (local FS)
    // Resources.  This must be achieved with minimal compilation time,
    // since encoding real assets takes time.  Each time a debug
    // Resource is fetched, it should reopen the file, since the user
    // may be iterating on development of the Resource's content.
    class Mapper {
    public:
	// Mapper may not be instantiated.
	//
	// TODO: Allow instantiation but move static assets into
	// templated type.
	Mapper() = delete;

	// Fetch creates and retrieves a unique smart-pointer to a
	// Resource.
	static std::unique_ptr<Resource> Fetch(ID) noexcept(false);

    private:
	struct resDefn {
	    size_t               compressed_length;
	    size_t               decompressed_length;
	    const unsigned char* content;
	};

	// friend std::map<ID, resDefn>::operator[];

	static std::map<ID, const resDefn> mappings;

	// Here, all names of assets are defined.  Each must have an ID
	// associated with it.

	// dat.txt
	static const size_t        dat_txt_len;
	static const unsigned char dat_txt[];
    };
}; // namespace res

#endif
