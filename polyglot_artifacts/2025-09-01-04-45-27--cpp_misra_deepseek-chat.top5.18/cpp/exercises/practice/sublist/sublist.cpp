#include "sublist.h"
#include <vector>
#include <algorithm>

namespace sublist {

template <typename T>
List_comparison sublist(const std::vector<T>& list_a, const std::vector<T>& list_b) {
    // Check if the lists are equal
    if (list_a == list_b) {
        return List_comparison::equal;
    }
    
    // Check if list_a is a superlist of list_b (list_b is a sublist of list_a)
    if (list_a.size() > list_b.size()) {
        // Check if list_b is empty, which is always a sublist
        if (list_b.empty()) {
            return List_comparison::superlist;
        }
        // Check all possible starting positions in list_a where list_b could fit
        for (typename std::vector<T>::size_type i = 0; i <= list_a.size() - list_b.size(); ++i) {
            if (std::equal(list_b.begin(), list_b.end(), list_a.begin() + i)) {
                return List_comparison::superlist;
            }
        }
    }
    
    // Check if list_a is a sublist of list_b (list_b is a superlist of list_a)
    if (list_a.size() < list_b.size()) {
        // Check if list_a is empty, which is always a sublist
        if (list_a.empty()) {
            return List_comparison::sublist;
        }
        // Check all possible starting positions in list_b where list_a could fit
        for (typename std::vector<T>::size_type i = 0; i <= list_b.size() - list_a.size(); ++i) {
            if (std::equal(list_a.begin(), list_a.end(), list_b.begin() + i)) {
                return List_comparison::sublist;
            }
        }
    }
    
    // If none of the above conditions are true
    return List_comparison::unequal;
}

// Explicit template instantiation
template List_comparison sublist(const std::vector<int>&, const std::vector<int>&);

}  // namespace sublist
