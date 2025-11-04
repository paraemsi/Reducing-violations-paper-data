#include "sublist.h"

#include <cstddef>   // for std::size_t

namespace sublist
{
namespace {

/*  Determine whether |candidate| appears contiguously inside |host|. */
[[nodiscard]] auto is_sublist(const std::vector<std::int32_t>& candidate,
                              const std::vector<std::int32_t>& host) noexcept -> bool
{
    if (candidate.empty())
    {
        /*  An empty list is trivially a sublist of any list. */
        return true;
    }

    const std::size_t candidate_length { candidate.size() };

    if (candidate_length > host.size())
    {
        return false;
    }

    const std::size_t last_start { host.size() - candidate_length };

    for (std::size_t i { 0U }; i <= last_start; ++i)
    {
        bool match { true };

        for (std::size_t j { 0U }; j < candidate_length; ++j)
        {
            if (host[(i + j)] != candidate[j])
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

}  // unnamed namespace

auto classify(const std::vector<std::int32_t>& a,
              const std::vector<std::int32_t>& b) noexcept -> Comparison
{
    if (a == b)
    {
        return Comparison::Equal;
    }

    if (is_sublist(b, a))
    {
        return Comparison::Superlist;
    }

    if (is_sublist(a, b))
    {
        return Comparison::Sublist;
    }

    return Comparison::Unequal;
}

/*  Public adapter matching exercise API.
 *  Returns result as sublist::List_comparison.
 */
auto sublist(const std::vector<std::int32_t>& a,
             const std::vector<std::int32_t>& b) noexcept -> List_comparison
{
    const Comparison internal_result { classify(a, b) };

    switch (internal_result)
    {
        case Comparison::Equal:
        {
            return List_comparison::equal;
        }
        case Comparison::Sublist:
        {
            return List_comparison::sublist;
        }
        case Comparison::Superlist:
        {
            return List_comparison::superlist;
        }
        default:
        {
            return List_comparison::unequal;
        }
    }
}

}  // namespace sublist
