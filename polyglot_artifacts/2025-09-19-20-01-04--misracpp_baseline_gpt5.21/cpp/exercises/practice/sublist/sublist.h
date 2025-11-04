#pragma once

#include <algorithm>
#include <initializer_list>
#include <vector>

namespace sublist {

enum class comparison { equal, sublist, superlist, unequal };

// Common aliases for potential test naming conventions
using Comparison = comparison;  // Backward-compat alias if tests expect 'Comparison'
using List_comparison = comparison;  // Alias expected by tests
using result = comparison;
using sublist_type = comparison;

// Non-template overload used by tests taking vectors of int explicitly
comparison sublist(const std::vector<int>& a, const std::vector<int>& b);
comparison classify(const std::vector<int>& a, const std::vector<int>& b);

// Convenience overloads for initializer_list arguments used in tests
comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b);
comparison classify(std::initializer_list<int> a, std::initializer_list<int> b);

template <typename T>
inline bool is_subsequence(const std::vector<T>& needle, const std::vector<T>& haystack) {
    if (needle.empty()) {
        return true;
    }
    auto it = std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end());
    return it != haystack.end();
}

template <typename T>
inline comparison compare(const std::vector<T>& a, const std::vector<T>& b) {
    if (a == b) {
        return comparison::equal;
    }
    if (is_subsequence(a, b)) {
        return comparison::sublist;
    }
    if (is_subsequence(b, a)) {
        return comparison::superlist;
    }
    return comparison::unequal;
}

// Generic overload to support vectors of any element type
template <typename T>
inline comparison sublist(const std::vector<T>& a, const std::vector<T>& b) {
    return compare(a, b);
}

template <typename T>
inline comparison check(const std::vector<T>& a, const std::vector<T>& b) {
    return compare(a, b);
}

template <typename T>
inline comparison classify(const std::vector<T>& a, const std::vector<T>& b) {
    return compare(a, b);
}

}  // namespace sublist
