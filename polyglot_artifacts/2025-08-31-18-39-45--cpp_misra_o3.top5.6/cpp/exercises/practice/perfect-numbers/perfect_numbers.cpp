#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

auto classify(int32 number) -> classification
{
    /* Non-positive integers are invalid – signal caller error. */
    if(number <= static_cast<int32>(0))
    {
        throw std::domain_error("number must be positive");
    }

    /* By convention, 1 is considered deficient. */
    if(number == static_cast<int32>(1))
    {
        return classification::deficient;
    }

    uint32 u_number{static_cast<uint32>(number)}; /* signed → unsigned: number is > 0 */
    uint32 sum{static_cast<uint32>(1U)};

    for(uint32 i{static_cast<uint32>(2U)};
        (static_cast<uint64>(i) * static_cast<uint64>(i)) <= static_cast<uint64>(u_number);
        ++i)
    {
        if((u_number % i) == static_cast<uint32>(0U))
        {
            sum += i;

            uint32 other{u_number / i};
            if(other != i)
            {
                sum += other;
            }
        }
    }

    if(sum == u_number)
    {
        return classification::perfect;
    }
    else if(sum > u_number)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
