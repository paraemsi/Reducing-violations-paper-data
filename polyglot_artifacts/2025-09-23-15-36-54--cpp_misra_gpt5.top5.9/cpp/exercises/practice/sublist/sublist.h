#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <initializer_list>

namespace sublist {

// Relationship between two lists A and B
enum class Comparison {
    equal,
    sublist,
    superlist,
    unequal
};

using List_comparison = Comparison;

template <typename T>
inline bool contains_subsequence(const std::vector<T>& haystack, const std::vector<T>& needle)
{
    const std::size_t hsize = haystack.size();
    const std::size_t nsize = needle.size();

    if (nsize == static_cast<std::size_t>(0U)) {
        return true;
    }

    if (hsize < nsize) {
        return false;
    }

    for (std::size_t i = static_cast<std::size_t>(0U); ((i + nsize) <= hsize); ++i) {
        bool all_equal = true;
        for (std::size_t j = static_cast<std::size_t>(0U); (j < nsize); ++j) {
            if (!(haystack[i + j] == needle[j])) {
                all_equal = false;
                break;
            }
        }
        if (all_equal) {
            return true;
        }
    }

    return false;
}

// Primary API: determine relation between lists A and B
template <typename T>
inline Comparison classify(const std::vector<T>& a, const std::vector<T>& b)
{
    if (a == b) {
        return Comparison::equal;
    }

    if (contains_subsequence<T>(a, b)) {
        return Comparison::superlist;
    }

    if (contains_subsequence<T>(b, a)) {
        return Comparison::sublist;
    }

    return Comparison::unequal;
}

template <typename T>
inline Comparison sublist(const std::vector<T>& a, const std::vector<T>& b)
{
    return classify<T>(a, b);
}


inline Comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b)
{
    return classify<std::int32_t>(a, b);
}

}  // namespace sublist
