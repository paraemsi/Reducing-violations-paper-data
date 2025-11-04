#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

namespace
{

[[nodiscard]] auto classify_impl(std::uint32_t n) -> perfect_numbers::classification
{
    if(n == 0U)
    {
        throw std::domain_error("Classification is only possible for positive integers");
    }

    if(n == 1U)
    {
        return classification::deficient;
    }

    std::uint64_t sum {1U};

    for(std::uint32_t i {2U}; (static_cast<std::uint64_t>(i) * static_cast<std::uint64_t>(i)) <= static_cast<std::uint64_t>(n); ++i)
    {
        if((n % i) == 0U)
        {
            sum += static_cast<std::uint64_t>(i);
            const std::uint32_t other {n / i};
            if(other != i)
            {
                sum += static_cast<std::uint64_t>(other);
            }

            if(sum > static_cast<std::uint64_t>(n))
            {
                break;
            }
        }
    }

    if(sum == static_cast<std::uint64_t>(n))
    {
        return classification::perfect;
    }
    else if(sum > static_cast<std::uint64_t>(n))
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

} // unnamed namespace

[[nodiscard]] auto perfect_numbers::classify(std::int32_t n) -> classification
{
    if(n <= 0)
    {
        throw std::domain_error("Classification is only possible for positive integers");
    }

    return classify_impl(static_cast<std::uint32_t>(n));
}

}  // namespace perfect_numbers
