#include "utils.h"


uint64_t
engine::util::hash(const char* s, uint64_t seed)
{
        uint64_t hash = seed;
        while (*s)
                hash = hash * 101  +  static_cast<uint64_t>(*s ++);
        return hash;
}
