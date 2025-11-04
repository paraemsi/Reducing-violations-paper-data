#include "sublist.h"

namespace sublist {

template <typename T>
static bool is_sublist(const std::vector<T>& small, const std::vector<T>& big)
{
    if (small.empty()) {
        return true;
    }
    if (small.size() > big.size()) {
        return false;
    }
    for (index_t i = 0U; (i + static_cast<index_t>(small.size())) <= static_cast<index_t>(big.size()); ++i) {
        bool match = true;
        for (index_t j = 0U; j < static_cast<index_t>(small.size()); ++j) {
            if (!(big[i + j] == small[j])) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

static Comparison compare_int(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b)
{
    if (a == b) {
        return Comparison::Equal;
    }
    if (is_sublist(a, b)) {
        return Comparison::Sublist;
    }
    if (is_sublist(b, a)) {
        return Comparison::Superlist;
    }
    return Comparison::Unequal;
}

Comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b)
{
    return compare_int(a, b);
}

}  // namespace sublist
