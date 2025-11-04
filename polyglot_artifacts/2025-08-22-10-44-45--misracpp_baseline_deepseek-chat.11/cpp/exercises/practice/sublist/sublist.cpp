#include "sublist.h"
#include <vector>
using namespace std;

namespace sublist {

// Check if list2 is a sublist of list1 (precondition: list1.size() >= list2.size())
bool isSublist(const vector<int>& list1, const vector<int>& list2) {
    if (list2.empty()) return true;
    if (list1.size() < list2.size()) return false;
    
    for (size_t i = 0; i <= list1.size() - list2.size(); ++i) {
        bool found = true;
        for (size_t j = 0; j < list2.size(); ++j) {
            if (list1[i + j] != list2[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return true;
        }
    }
    return false;
}

List_comparison sublist(const vector<int>& list1, const vector<int>& list2) {
    if (list1.size() == list2.size()) {
        // Check if they're equal
        bool areEqual = true;
        for (size_t i = 0; i < list1.size(); ++i) {
            if (list1[i] != list2[i]) {
                areEqual = false;
                break;
            }
        }
        if (areEqual) {
            return List_comparison::equal;
        }
    }
    
    // Check if list1 is a superlist of list2 (list1 contains list2)
    if (list1.size() > list2.size() && isSublist(list1, list2)) {
        return List_comparison::superlist;
    }
    
    // Check if list1 is a sublist of list2 (list2 contains list1)
    if (list2.size() > list1.size() && isSublist(list2, list1)) {
        return List_comparison::sublist;
    }
    
    return List_comparison::unequal;
}

}  // namespace sublist
