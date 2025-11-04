#include "sublist.h"

namespace sublist {

namespace {

/**
 * @brief Check if 'longer' contains 'shorter' as a contiguous sub-sequence.
 * @tparam T Element type
 * @param longer The vector to search within
 * @param shorter The vector to search for
 * @return true if 'shorter' is a sub-sequence of 'longer'
 */
template <typename T>
bool is_sublist(const std::vector<T>& longer, const std::vector<T>& shorter)
{
    if (shorter.empty()) {
        return true;
    }
    if (longer.size() < shorter.size()) {
        return false;
    }
    for (index_t i = 0U; (i + shorter.size()) <= longer.size(); ++i) {
        bool match = true;
        for (index_t j = 0U; j < shorter.size(); ++j) {
            if (!(longer[i + j] == shorter[j])) {
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

} // anonymous namespace

template <typename T>
List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b)
{
    if (a == b) {
        return List_comparison::equal;
    }
    if (is_sublist(a, b)) {
        return List_comparison::superlist;
    }
    if (is_sublist(b, a)) {
        return List_comparison::sublist;
    }
    return List_comparison::unequal;
}

template List_comparison sublist<std::int32_t>(const std::vector<std::int32_t>&, const std::vector<std::int32_t>&);
template List_comparison sublist<std::uint32_t>(const std::vector<std::uint32_t>&, const std::vector<std::uint32_t>&);
template List_comparison sublist<char>(const std::vector<char>&, const std::vector<char>&);

}  // namespace sublist
