#pragma once

#include <algorithm>
#include <iterator>
#include <vector>
#include <initializer_list>

namespace sublist {

enum class result { equal, sublist, superlist, unequal };
enum class List_comparison { equal, sublist, superlist, unequal };

template <typename Seq>
inline bool contains_subsequence(const Seq& haystack, const Seq& needle) {
    if (std::begin(needle) == std::end(needle)) {
        return true;
    }
    if (std::begin(haystack) == std::end(haystack)) {
        return false;
    }
    auto it = std::search(std::begin(haystack), std::end(haystack),
                          std::begin(needle), std::end(needle));
    return it != std::end(haystack);
}

template <typename Seq>
result classify(const Seq& a, const Seq& b) {
    const auto size_a = std::distance(std::begin(a), std::end(a));
    const auto size_b = std::distance(std::begin(b), std::end(b));
    if (size_a == size_b && std::equal(std::begin(a), std::end(a), std::begin(b))) {
        return result::equal;
    }
    if (contains_subsequence(a, b)) {
        return result::superlist;
    }
    if (contains_subsequence(b, a)) {
        return result::sublist;
    }
    return result::unequal;
}

template <typename Seq>
result check(const Seq& a, const Seq& b) {
    return classify(a, b);
}

template <typename Seq>
inline result compare(const Seq& a, const Seq& b) {
    return classify(a, b);
}


inline List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) {
    const auto r = classify(a, b);
    switch (r) {
        case result::equal: return List_comparison::equal;
        case result::sublist: return List_comparison::sublist;
        case result::superlist: return List_comparison::superlist;
        default: return List_comparison::unequal;
    }
}

inline List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b) {
    const auto r = classify(a, b);
    switch (r) {
        case result::equal: return List_comparison::equal;
        case result::sublist: return List_comparison::sublist;
        case result::superlist: return List_comparison::superlist;
        default: return List_comparison::unequal;
    }
}

}  // namespace sublist
