#include "sublist.h"
#include <vector>
#include <cstddef>

namespace sublist {

namespace {

template <typename T>
bool contains_sublist(const std::vector<T>& longer, const std::vector<T>& shorter) {
    if (shorter.empty()) return true;
    if (shorter.size() > longer.size()) return false;
    for (size_t i = 0; i <= longer.size() - shorter.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < shorter.size(); ++j) {
            if (longer[i + j] != shorter[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

template <typename T>
sublist::Comparison compare_impl(const std::vector<T>& A, const std::vector<T>& B) {
    if (A == B) {
        return sublist::Comparison::Equal;
    }
    if (contains_sublist(A, B)) {
        return sublist::Comparison::Superlist;
    }
    if (contains_sublist(B, A)) {
        return sublist::Comparison::Sublist;
    }
    return sublist::Comparison::Unequal;
}

} // anonymous namespace

namespace sublist {

Comparison compare(const std::vector<int>& A, const std::vector<int>& B) {
    return compare_impl(A, B);
}

Comparison compare(const std::vector<std::string>& A, const std::vector<std::string>& B) {
    return compare_impl(A, B);
}

} // namespace sublist
