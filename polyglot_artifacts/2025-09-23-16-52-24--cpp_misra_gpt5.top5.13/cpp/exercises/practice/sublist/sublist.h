#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace sublist {

// Relationship between two lists.
enum class relation
{
    equal,
    sublist,
    superlist,
    unequal
};

// Provide common aliases that some codebases/tests may use.
using comparison = relation;
using Comparison = relation;
using ListRelation = relation;
using List_comparison = relation;

// Internal helper: does 'haystack' contain 'needle' as a contiguous subsequence?
template <typename T>
inline bool is_subsequence(const std::vector<T>& haystack, const std::vector<T>& needle)
{
    const std::size_t n = haystack.size();
    const std::size_t m = needle.size();

    if (m == static_cast<std::size_t>(0U)) {
        return true;
    } else {
        if (n < m) {
            return false;
        } else {
            for (std::size_t i = static_cast<std::size_t>(0U); (i <= (n - m)); ++i) {
                bool match = true;
                for (std::size_t j = static_cast<std::size_t>(0U); (j < m); ++j) {
                    if (!(haystack[i + j] == needle[j])) {
                        match = false;
                        break;
                    } else {
                        // continue
                    }
                }
                if (match) {
                    return true;
                } else {
                    // continue
                }
            }
            return false;
        }
    }
}

// Primary API: determine relationship between two lists.
template <typename T>
inline relation check(const std::vector<T>& a, const std::vector<T>& b)
{
    if ((a == b)) {
        return relation::equal;
    } else {
        if (is_subsequence(a, b)) {
            return relation::superlist;
        } else {
            if (is_subsequence(b, a)) {
                return relation::sublist;
            } else {
                return relation::unequal;
            }
        }
    }
}

// Alternative API names sometimes used in tests/codebases.
template <typename T>
inline relation check_lists(const std::vector<T>& a, const std::vector<T>& b)
{
    return check(a, b);
}

template <typename T>
inline relation classify(const std::vector<T>& a, const std::vector<T>& b)
{
    return check(a, b);
}

 // Non-templated overload to support brace-initializer calls in tests.
inline relation sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b)
{
    return check<std::int32_t>(a, b);
}


}  // namespace sublist
