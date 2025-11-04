#include "perfect_numbers.h"

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

//--------------------------------------------------------------------------
//  Helper: compute the aliquot sum of a positive integer
//--------------------------------------------------------------------------
static auto aliquot_sum(std::uint32_t value) -> std::uint32_t
{
    // 1 is a proper divisor for every value greater than 1
    std::uint32_t sum {0U};

    for (std::uint32_t i {1U}; (static_cast<std::uint64_t>(i) * static_cast<std::uint64_t>(i)) <= static_cast<std::uint64_t>(value); ++i)
    {
        if ((value % i) == 0U)
        {
            const std::uint32_t pair {value / i};

            if ((i != value))
            {
                sum += i;
            }

            if ((pair != i) && (pair != value))
            {
                sum += pair;
            }
        }
    }

    return sum;
}

//--------------------------------------------------------------------------
//  classify : public interface
//--------------------------------------------------------------------------
auto classify(std::int32_t value) -> classification
{
    if (value <= 0)
    {
        throw std::domain_error("Classification is undefined for non-positive integers");
    }

    /*  Deliberate signed-to-unsigned conversion:
        The value is verified positive, therefore the cast is safe and avoids
        undefined behaviour while keeping the helper interface unsigned. */
    const std::uint32_t unsigned_value {static_cast<std::uint32_t>(value)};

    const std::uint32_t sum {aliquot_sum(unsigned_value)};

    if (sum == static_cast<std::uint32_t>(value))
    {
        return classification::perfect;
    }
    else if (sum > static_cast<std::uint32_t>(value))
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
