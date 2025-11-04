#include "sublist.h"

namespace sublist {

namespace {

bool is_sublist(const std::vector<value_type>& small, const std::vector<value_type>& big)
{
    if (small.empty()) {
        return true;
    }
    if (small.size() > big.size()) {
        return false;
    }
    for (std::size_t i = 0U; (i + small.size()) <= big.size(); ++i) {
        bool match = true;
        for (std::size_t j = 0U; j < small.size(); ++j) {
            if (big[i + j] != small[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

} // anonymous namespace

List_comparison sublist(const std::vector<value_type>& listA, const std::vector<value_type>& listB)
{
    if (listA == listB) {
        return List_comparison::equal;
    }
    if (is_sublist(listA, listB)) {
        return List_comparison::sublist;
    }
    if (is_sublist(listB, listA)) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

}  // namespace sublist
