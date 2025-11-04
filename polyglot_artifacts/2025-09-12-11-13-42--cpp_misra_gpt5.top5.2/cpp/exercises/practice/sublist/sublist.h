#pragma once

#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <vector>

namespace sublist {

enum class List_comparison : std::uint8_t {
    equal,
    sublist,
    superlist,
    unequal
};

template <typename T>
inline bool contains_sublist(const std::vector<T>& haystack, const std::vector<T>& needle)
{
    if (needle.empty()) {
        return true;
    }
    if (haystack.size() < needle.size()) {
        return false;
    }
    const typename std::vector<T>::const_iterator it = std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
    return (it != haystack.cend());
}

template <typename T>
inline List_comparison check(const std::vector<T>& a, const std::vector<T>& b)
{
    if ((a.size() == b.size())) {
        if (std::equal(a.cbegin(), a.cend(), b.cbegin())) {
            return List_comparison::equal;
        } else {
            return List_comparison::unequal;
        }
    } else if ((a.size() < b.size())) {
        if (contains_sublist(b, a)) {
            return List_comparison::sublist;
        } else {
            return List_comparison::unequal;
        }
    } else {
        if (contains_sublist(a, b)) {
            return List_comparison::superlist;
        } else {
            return List_comparison::unequal;
        }
    }
}
 
template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b)
{
    return check(a, b);
}


inline List_comparison sublist(std::initializer_list<std::int32_t> a, std::initializer_list<std::int32_t> b)
{
    const std::vector<std::int32_t> va(a);
    const std::vector<std::int32_t> vb(b);
    return check(va, vb);
}
 
}  // namespace sublist
