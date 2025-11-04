#pragma once

#include <vector>
#include <cstddef>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

template <typename T>
bool is_subsequence(const std::vector<T>& haystack, const std::vector<T>& needle)
{
    if (needle.empty()) {
        return true;
    }
    if (needle.size() > haystack.size()) {
        return false;
    }
    const std::size_t limit = haystack.size() - needle.size();
    for (std::size_t i = 0; i <= limit; ++i) {
        bool match = true;
        for (std::size_t j = 0; j < needle.size(); ++j) {
            if (!(haystack[i + j] == needle[j])) {
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
List_comparison sublist(const std::vector<T>& list_a, const std::vector<T>& list_b)
{
    if (list_a == list_b) {
        return List_comparison::equal;
    }
    if (is_subsequence(list_a, list_b)) {
        return List_comparison::superlist;
    }
    if (is_subsequence(list_b, list_a)) {
        return List_comparison::sublist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
