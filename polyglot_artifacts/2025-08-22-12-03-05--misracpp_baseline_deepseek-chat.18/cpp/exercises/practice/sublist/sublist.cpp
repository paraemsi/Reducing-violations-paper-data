#include "sublist.h"
#include <vector>
using namespace std;

namespace sublist {

List_comparison sublist(const vector<int>& list1, const vector<int>& list2) {
    // Check if the lists are equal
    if (list1 == list2) {
        return List_comparison::equal;
    }
    
    // Check if list1 is a sublist of list2
    if (list1.size() < list2.size()) {
        // An empty list is always a sublist of any non-empty list
        if (list1.empty()) {
            return List_comparison::sublist;
        }
        // Check all possible starting positions in list2
        for (size_t i = 0; i <= list2.size() - list1.size(); ++i) {
            bool match = true;
            for (size_t j = 0; j < list1.size(); ++j) {
                if (list2[i + j] != list1[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Check if list1 is a superlist of list2 (i.e., list2 is a sublist of list1)
    if (list1.size() > list2.size()) {
        // An empty list2 means list1 is always a superlist
        if (list2.empty()) {
            return List_comparison::superlist;
        }
        // Check all possible starting positions in list1
        for (size_t i = 0; i <= list1.size() - list2.size(); ++i) {
            bool match = true;
            for (size_t j = 0; j < list2.size(); ++j) {
                if (list1[i + j] != list2[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return List_comparison::superlist;
            }
        }
    }
    
    // If none of the above, the lists are unequal
    return List_comparison::unequal;
}

}  // namespace sublist
