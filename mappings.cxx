#include "id.hpp"
#include "mapper.hpp"

namespace res {
    std::map<ID, const Mapper::resDefn> Mapper::mappings{
	// TODO: Generate each using the phx tool, in a separate file.
	// TODO: use std::array with an "interface" map value?

	// res/dat.txt
	{ ID::dat_txt,
	  {
	    .compressed_length = std::extent<decltype(dat_txt)>::value,
	    .decompressed_length = dat_txt_len,
	    .content             = dat_txt,
	  } },
    };
}; // namespace res
