#include "sublist.h"

#include <cstddef>      // for std::size_t
#include <vector>

namespace {
/* Check whether `needle` appears as a contiguous sub-sequence of `haystack`. */
auto is_subsequence(const std::vector<std::int32_t>& needle,
                    const std::vector<std::int32_t>& haystack) noexcept -> bool
{
    if (needle.empty()) {
        return true;
    }

    if (needle.size() > haystack.size()) {
        return false;
    }

    const std::size_t last_start { haystack.size() - needle.size() };

    for (std::size_t i { 0U }; i <= last_start; ++i) {
        bool match { true };

        for (std::size_t j { 0U }; j < needle.size(); ++j) {
            if (haystack[(i + j)] != needle[j]) {
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
}  // unnamed namespace

namespace sublist {

auto sublist(const std::vector<std::int32_t>& listA,
             const std::vector<std::int32_t>& listB) -> List_comparison
{
    if (listA == listB) {
        return List_comparison::equal;
    }

    const bool a_in_b { is_subsequence(listA, listB) };
    const bool b_in_a { is_subsequence(listB, listA) };

    if (a_in_b && (listA.size() < listB.size())) {
        return List_comparison::sublist;
    }

    if (b_in_a && (listB.size() < listA.size())) {
        return List_comparison::superlist;
    }

    return List_comparison::unequal;
}

}  // namespace sublist
