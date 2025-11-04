#pragma once

#include <vector>
#include <algorithm>
#include <iterator>   // for std::search (some standard libraries require <iterator>)

namespace sublist {

// The possible relationship outcomes between two lists.
enum class List_comparison { equal, sublist, superlist, unequal };

/*
 * Classify the relationship between list1 and list2 according to the rules
 * specified in the problem statement.
 *
 * Implemented as a function template so it can work with vectors whose element
 * type supports equality comparison.
 */
template <typename T>
inline List_comparison classify(const std::vector<T>& list1, const std::vector<T>& list2) {
    // Case: lists are exactly equal
    if (list1 == list2) {
        return List_comparison::equal;
    }

    // When list1 is shorter, it can only be a sublist of list2
    if (list1.size() < list2.size()) {
        if (list1.empty() ||
            std::search(list2.begin(), list2.end(),
                        list1.begin(), list1.end()) != list2.end()) {
            return List_comparison::sublist;
        }
    }
    // When list1 is longer, it can only be a superlist of list2
    else if (list1.size() > list2.size()) {
        if (list2.empty() ||
            std::search(list1.begin(), list1.end(),
                        list2.begin(), list2.end()) != list1.end()) {
            return List_comparison::superlist;
        }
    }

    // If none of the above conditions were met, the lists are unequal
    return List_comparison::unequal;
}

/*
 * Non-template wrapper required by the unit tests.
 * Works with the default element type `int`.
 */
List_comparison sublist(const std::vector<int>& list1, const std::vector<int>& list2);

}  // namespace sublist
