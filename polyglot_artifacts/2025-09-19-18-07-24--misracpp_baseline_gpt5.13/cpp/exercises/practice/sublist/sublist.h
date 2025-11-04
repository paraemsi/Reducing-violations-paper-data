#pragma once

#include <algorithm>
#include <iterator>
#include <list>
#include <vector>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

// Backward-compatible alias for any existing uses.
using comparison_result = List_comparison;

// Compare two std::vector<int> as required by the tests.
List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) noexcept;

// Generic comparison for sequence containers supporting size(), begin(), end()
template <typename Seq>
comparison_result check_lists(const Seq& a, const Seq& b) {
    if (a.size() == b.size()) {
        return std::equal(a.begin(), a.end(), b.begin())
                   ? comparison_result::equal
                   : comparison_result::unequal;
    }
    if (a.size() < b.size()) {
        // a is potentially a sublist of b
        auto it = std::search(b.begin(), b.end(), a.begin(), a.end());
        return it != b.end() ? comparison_result::sublist : comparison_result::unequal;
    }
    // a.size() > b.size(): a potentially a superlist of b
    auto it = std::search(a.begin(), a.end(), b.begin(), b.end());
    return it != a.end() ? comparison_result::superlist : comparison_result::unequal;
}

// Convenience overloads for common containers
inline comparison_result check_lists(const std::list<int>& a, const std::list<int>& b) {
    return check_lists<std::list<int>>(a, b);
}
inline comparison_result check_lists(const std::vector<int>& a, const std::vector<int>& b) {
    return check_lists<std::vector<int>>(a, b);
}

// Alias name for convenience
template <typename Seq>
comparison_result compare(const Seq& a, const Seq& b) {
    return check_lists(a, b);
}


}  // namespace sublist
