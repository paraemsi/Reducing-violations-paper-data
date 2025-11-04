#include "sublist.h"

#include <cstddef>

namespace sublist {

namespace
{

template <typename T>
bool is_sublist(const std::vector<T>& small, const std::vector<T>& big)
{
    const std::size_t small_size = small.size();
    const std::size_t big_size = big.size();

    if (small_size == 0U)
    {
        return true;
    }
    if (small_size > big_size)
    {
        return false;
    }

    for (std::size_t i = 0U; (i + small_size) <= big_size; ++i)
    {
        bool match = true;
        for (std::size_t j = 0U; j < small_size; ++j)
        {
            if (!(big[i + j] == small[j]))
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            return true;
        }
    }
    return false;
}

} // anonymous namespace

template <typename T>
List_comparison sublist(const std::vector<T>& listA, const std::vector<T>& listB)
{
    if (listA == listB)
    {
        return List_comparison::equal;
    }
    if (is_sublist(listA, listB))
    {
        return List_comparison::sublist;
    }
    if (is_sublist(listB, listA))
    {
        return List_comparison::superlist;
    }
    return List_comparison::unequal;
}

// Explicit template instantiations for common types
template List_comparison sublist<std::int32_t>(const std::vector<std::int32_t>&, const std::vector<std::int32_t>&);
template List_comparison sublist<std::uint32_t>(const std::vector<std::uint32_t>&, const std::vector<std::uint32_t>&);
template List_comparison sublist<char>(const std::vector<char>&, const std::vector<char>&);

}  // namespace sublist
