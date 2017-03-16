#include "utils.h"


uint64_t
engine::util::hash(const char* s, uint64_t seed)
{
        uint64_t hash = seed;
        while (*s)
                hash = hash * 101  +  static_cast<uint64_t>(*s ++);
        return hash;
}

static const std::locale loc;

std::string
engine::util::toupper(const std::string& content)
{
        std::string upper;
        upper.resize(content.size());
        for (unsigned i = 0; i < content.size();i ++) {
                upper[i] = std::toupper(content[i], loc);
        }
        return upper;
}

unsigned
engine::util::ed(const std::string& a, const std::string& b)
{
        const unsigned a_len = static_cast<unsigned>(a.length()), b_len = static_cast<unsigned>(b.length());

        if (a_len == 0) return b_len;
        if (b_len == 0) return a_len;

        unsigned i, j, i_prv, i_crt, d[2][b_len + 1];

        for (j = 0; j <= b_len; j++) {
                d[0][j] = j;
        }
        i_prv = 0;
        i_crt = 1;
        for (i = 1; i <= a_len; i++) {
                d[i_crt][0] = i;
                for (j = 1; j <= b_len; j++) {
                        d[i_crt][j] = std::min(std::min(d[i_prv][j] + 1,d[i_crt][j-1] + 1),
                                                        d[i_prv][j-1] + (a[i-1] == b[j-1] ? 0 : 1));
                }
                i_prv = i_prv ? 0 : 1;
                i_crt = i_crt ? 0 : 1;
        }

        return d[i_prv][b_len];
}
