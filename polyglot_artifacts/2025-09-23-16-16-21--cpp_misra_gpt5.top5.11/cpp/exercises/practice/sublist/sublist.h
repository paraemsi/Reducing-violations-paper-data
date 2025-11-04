#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <vector>

namespace sublist {

enum class comparison : std::uint8_t {
    equal,
    superlist,
    sublist,
    unequal
};

using List_comparison = comparison;

List_comparison sublist(const std::vector<std::int32_t> & a, const std::vector<std::int32_t> & b);
List_comparison sublist(std::initializer_list<std::int32_t> a, std::initializer_list<std::int32_t> b);

template <typename T>
inline bool contains_subsequence(const std::vector<T> & haystack, const std::vector<T> & needle)
{
    if (needle.empty()) {
        return true;
    }

    if (haystack.empty()) {
        return false;
    }

    if (haystack.size() < needle.size()) {
        return false;
    }

    typename std::vector<T>::const_iterator it = std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
    return (it != haystack.cend());
}

template <typename T>
inline comparison classify(const std::vector<T> & a, const std::vector<T> & b)
{
    if ((a == b)) {
        return comparison::equal;
    }

    if ((contains_subsequence(a, b))) {
        return comparison::superlist;
    }

    if ((contains_subsequence(b, a))) {
        return comparison::sublist;
    }

    return comparison::unequal;
}

}  // namespace sublist
