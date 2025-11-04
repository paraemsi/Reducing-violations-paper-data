#pragma once
#include <algorithm>
#include <cstdint>
#include <cstddef>
#include <initializer_list>
#include <vector>

namespace sublist {

enum class List_comparison : std::uint8_t {
    equal = 0U,
    sublist = 1U,
    superlist = 2U,
    unequal = 3U
};

template <typename T>
inline bool contains_subsequence(const std::vector<T>& haystack, const std::vector<T>& needle)
{
    if (needle.empty()) {
        return true;
    }

    const typename std::vector<T>::size_type haystack_size = haystack.size();
    const typename std::vector<T>::size_type needle_size = needle.size();

    if (haystack_size < needle_size) {
        return false;
    }

    const typename std::vector<T>::size_type last_start = (haystack_size - needle_size);
    for (typename std::vector<T>::size_type i = static_cast<typename std::vector<T>::size_type>(0); i <= last_start; ++i) {
        bool match = true;
        for (typename std::vector<T>::size_type j = static_cast<typename std::vector<T>::size_type>(0); j < needle_size; ++j) {
            if (!(haystack[static_cast<typename std::vector<T>::size_type>(i + j)] == needle[static_cast<typename std::vector<T>::size_type>(j)])) {
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

template <typename T>
inline List_comparison check(const std::vector<T>& a, const std::vector<T>& b)
{
    if ((a.size() == b.size()) && (std::equal(a.begin(), a.end(), b.begin()))) {
        return List_comparison::equal;
    }

    if (contains_subsequence(a, b)) {
        return List_comparison::superlist;
    }

    if (contains_subsequence(b, a)) {
        return List_comparison::sublist;
    }

    return List_comparison::unequal;
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b)
{
    return check<T>(a, b);
}

List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b);
List_comparison sublist(std::initializer_list<std::int32_t> a, std::initializer_list<std::int32_t> b);

}  // namespace sublist
