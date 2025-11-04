#pragma once

#include <algorithm>
#include <iterator>
#include <vector>

namespace sublist {

enum class List_comparison {
    equal,
    sublist,
    superlist,
    unequal
};

template <typename Seq>
inline bool is_sublist(const Seq& small, const Seq& big) {
    using std::begin;
    using std::end;
    auto sb = begin(small);
    auto se = end(small);
    auto bb = begin(big);
    auto be = end(big);

    if (sb == se) {
        return true;
    }

    auto small_len = std::distance(sb, se);
    auto big_len = std::distance(bb, be);
    if (small_len > big_len) {
        return false;
    }

    auto it = std::search(bb, be, sb, se);
    return it != be;
}

template <typename Seq>
inline List_comparison check_lists(const Seq& a, const Seq& b) {
    using std::begin;
    using std::end;
    auto ab = begin(a);
    auto ae = end(a);
    auto bb = begin(b);
    auto be = end(b);

    if (std::distance(ab, ae) == std::distance(bb, be) &&
        std::equal(ab, ae, bb)) {
        return List_comparison::equal;
    }
    if (is_sublist(a, b)) {
        return List_comparison::sublist;
    }
    if (is_sublist(b, a)) {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

template <typename Seq>
inline List_comparison classify(const Seq& a, const Seq& b) {
    return check_lists(a, b);
}

List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b);

}  // namespace sublist
