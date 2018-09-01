#include "mapper.hpp"

namespace res {
    const size_t        Mapper::dat_txt_len = 12;
    const unsigned char Mapper::dat_txt[]   = {
#include "dat.txt"
    };
}; // namespace res
