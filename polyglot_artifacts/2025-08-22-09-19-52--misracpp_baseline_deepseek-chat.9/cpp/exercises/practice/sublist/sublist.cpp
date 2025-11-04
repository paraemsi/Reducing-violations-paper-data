#include "sublist.h"
#include <vector>
using namespace std;

namespace sublist {

List_comparison sublist(const vector<int>& list_a, const vector<int>& list_b) {
    // Check if they're equal
    if (list_a == list_b) {
        return List_comparison::equal;
    }
    
    // Check if list_a is a superlist of list_b (list_a contains list_b)
    if (list_a.size() > list_b.size()) {
        for (size_t i = 0; i <= list_a.size() - list_b.size(); ++i) {
            bool found = true;
            for (size_t j = 0; j < list_b.size(); ++j) {
                if (list_a[i + j] != list_b[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::superlist;
            }
        }
    }
    // Check if list_a is a sublist of list_b (list_b contains list_a)
    else if (list_a.size() < list_b.size()) {
        for (size_t i = 0; i <= list_b.size() - list_a.size(); ++i) {
            bool found = true;
            for (size_t j = 0; j < list_a.size(); ++j) {
                if (list_b[i + j] != list_a[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return List_comparison::sublist;
            }
        }
    }
    
    // Handle cases where sizes are equal but contents are different
    // Also, if none of the above conditions were met
    return List_comparison::unequal;
}

}  // namespace sublist
