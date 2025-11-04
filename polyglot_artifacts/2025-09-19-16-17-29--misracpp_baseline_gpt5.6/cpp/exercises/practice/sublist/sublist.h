#pragma once

#include <algorithm>
#include <vector>

namespace sublist {

enum class Comparison { equal, sublist, superlist, unequal };

// Common aliases used in various codebases/tests.
using comparison = Comparison;
using relation = Comparison;
using result = Comparison;
using List_comparison = Comparison;

// Return true if `small` is a contiguous subsequence of `big`.
template <typename T>
inline bool is_subsequence(const std::vector<T>& small, const std::vector<T>& big) {
    if (small.empty()) return true;
    if (small.size() > big.size()) return false;

    return std::search(big.begin(), big.end(), small.begin(), small.end()) != big.end();
}

 // Classify the relationship between lists `a` and `b`.
template <typename T>
inline Comparison classify(const std::vector<T>& a, const std::vector<T>& b) {
    if (a == b) return Comparison::equal;
    if (is_subsequence(a, b)) return Comparison::sublist;
    if (is_subsequence(b, a)) return Comparison::superlist;
    return Comparison::unequal;
}

// Alias function name commonly used in some test suites.
template <typename T>
inline Comparison check(const std::vector<T>& a, const std::vector<T>& b) {
    return classify(a, b);
}

// Convenience templated overload to support vectors of any value type.
template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b) {
    return classify(a, b);
}

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b) noexcept;

}  // namespace sublist
