#pragma once

#include <vector>
#include <algorithm>
#include <cstdint>
#include <initializer_list>

namespace sublist {

/*  The result of comparing two lists                                  */
enum class List_comparison {
    equal,      /* Lists are exactly the same      */
    sublist,    /* First list  is contained in second */
    superlist,  /* Second list is contained in first  */
    unequal     /* None of the above                  */
};

/*  Return true when `smaller` occurs as a contiguous subsequence
 *  within `larger`.                                                  */
template <typename T>
inline bool is_contiguous_subsequence(const std::vector<T>& smaller,
                                      const std::vector<T>& larger)
{
    if ((smaller.empty())) {
        return true;
    }

    auto itr = std::search(larger.begin(),
                           larger.end(),
                           smaller.begin(),
                           smaller.end());

    return (itr != larger.end());
}

/*  Compare two lists and return their relationship.                   */
template <typename T>
inline List_comparison compare_vectors(const std::vector<T>& first,
                                       const std::vector<T>& second)
{
    if ((first == second)) {
        return List_comparison::equal;
    }

    if ((first.empty())) {
        return List_comparison::sublist;
    }

    if ((second.empty())) {
        return List_comparison::superlist;
    }

    if ((first.size() < second.size())) {
        if (is_contiguous_subsequence(first, second)) {
            return List_comparison::sublist;
        } else {
            return List_comparison::unequal;
        }
    }

    if ((first.size() > second.size())) {
        if (is_contiguous_subsequence(second, first)) {
            return List_comparison::superlist;
        } else {
            return List_comparison::unequal;
        }
    }

    /* Sizes are equal but contents differ. */
    return List_comparison::unequal;
}

inline List_comparison sublist(std::initializer_list<int> first,
                               std::initializer_list<int> second)
{
    return compare_vectors<int>(std::vector<int>(first),
                                std::vector<int>(second));
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& first,
                               const std::vector<T>& second)
{
    return compare_vectors<T>(first, second);
}

}  // namespace sublist
