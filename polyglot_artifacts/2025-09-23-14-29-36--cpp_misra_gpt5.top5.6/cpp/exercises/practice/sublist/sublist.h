#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>

namespace sublist {

enum class List_comparison
{
    equal,
    sublist,
    superlist,
    unequal
};

template <typename T>
inline List_comparison check(const std::vector<T>& a, const std::vector<T>& b) noexcept
{
    if ((a == b)) {
        return (List_comparison::equal);
    }

    if ((b.empty())) {
        return (List_comparison::superlist);
    }

    if ((a.empty())) {
        return (List_comparison::sublist);
    }

    const typename std::vector<T>::const_iterator it_a = std::search(a.begin(), a.end(), b.begin(), b.end());
    if ((it_a != a.end())) {
        return (List_comparison::superlist);
    }

    const typename std::vector<T>::const_iterator it_b = std::search(b.begin(), b.end(), a.begin(), a.end());
    if ((it_b != b.end())) {
        return (List_comparison::sublist);
    }

    return (List_comparison::unequal);
}

template <typename T>
inline List_comparison sublist(const std::vector<T>& a, const std::vector<T>& b) noexcept
{
    return (check<T>(a, b));
}

List_comparison check(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) noexcept;

List_comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b) noexcept;

}  // namespace sublist
