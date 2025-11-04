#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include <initializer_list>

namespace sublist {

/*
 * Relationship between two lists as described in the exercise.
 */
enum class List_comparison
{
    equal,      // Lists are identical
    sublist,    // First list is contained in the second
    superlist,  // First list contains the second
    unequal     // None of the above
};

/*
 * Compare two lists and return their relationship.
 * The function is implemented in the header to allow usage with any
 * element type that supports equality comparison.
 */
template <typename T>
inline List_comparison sublist(const std::vector<T>& listA, const std::vector<T>& listB)
{
    /* Equal check comes first for an early exit. */
    if ((listA == listB))
    {
        return List_comparison::equal;
    }

    /* Handle the “first is sublist of second” scenario. */
    if (listA.size() < listB.size())
    {
        if (listA.empty())
        {
            /* An empty list is a sublist of any other list. */
            return List_comparison::sublist;
        }

        const auto itSub = std::search(
            listB.begin(), listB.end(),
            listA.begin(), listA.end());

        if (itSub != listB.end())
        {
            return List_comparison::sublist;
        }
    }

    /* Handle the “first is superlist of second” scenario. */
    if (listA.size() > listB.size())
    {
        if (listB.empty())
        {
            /* Any non-empty list is a superlist of an empty list. */
            return List_comparison::superlist;
        }

        const auto itSuper = std::search(
            listA.begin(), listA.end(),
            listB.begin(), listB.end());

        if (itSuper != listA.end())
        {
            return List_comparison::superlist;
        }
    }

    /* None of the cases matched – the lists are unequal. */
    return List_comparison::unequal;
}

/*
 * Convenience overloads that accept brace-initialised lists directly,
 * mirroring the invocations used from the unit tests.
 */
template <typename T>
inline List_comparison sublist(std::initializer_list<T> listAInit,
                               std::initializer_list<T> listBInit)
{
    const std::vector<T> listA(listAInit);
    const std::vector<T> listB(listBInit);

    return sublist(listA, listB);
}

}  // namespace sublist
