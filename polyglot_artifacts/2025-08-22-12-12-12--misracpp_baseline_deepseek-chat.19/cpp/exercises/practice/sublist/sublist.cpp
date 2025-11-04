#include "sublist.h"
#include <vector>
using namespace std;

namespace sublist {

// Helper function to check if list2 is found in list1 starting at index i
bool isSublistAt(const vector<int>& list1, const vector<int>& list2, size_t start) {
    for (size_t j = 0; j < list2.size(); ++j) {
        if (list1[start + j] != list2[j]) {
            return false;
        }
    }
    return true;
}

List_comparison sublist(const vector<int>& list1, const vector<int>& list2) {
    // Check for equality first
    if (list1.size() == list2.size()) {
        bool equal = true;
        for (size_t i = 0; i < list1.size(); ++i) {
            if (list1[i] != list2[i]) {
                equal = false;
                break;
            }
        }
        if (equal) {
            return List_comparison::equal;
        }
    }
    
    // Check if list1 is a sublist of list2 (list1 is contained within list2)
    if (list1.size() < list2.size()) {
        // Handle empty list1
        if (list1.empty()) {
            return List_comparison::sublist;
        }
        // Check each possible starting position in list2
        for (size_t i = 0; i + list1.size() <= list2.size(); ++i) {
            if (isSublistAt(list2, list1, i)) {
                return List_comparison::sublist;
            }
        }
    } else if (list1.size() == list2.size()) {
        // Already checked for equality above, so nothing to do here
    }
    
    // Check if list1 is a superlist of list2 (list2 is a sublist of list1)
    if (list1.size() > list2.size()) {
        // Handle empty list2
        if (list2.empty()) {
            return List_comparison::superlist;
        }
        // Check each possible starting position in list1
        for (size_t i = 0; i + list2.size() <= list1.size(); ++i) {
            if (isSublistAt(list1, list2, i)) {
                return List_comparison::superlist;
            }
        }
    }
    
    return List_comparison::unequal;
}

}  // namespace sublist
