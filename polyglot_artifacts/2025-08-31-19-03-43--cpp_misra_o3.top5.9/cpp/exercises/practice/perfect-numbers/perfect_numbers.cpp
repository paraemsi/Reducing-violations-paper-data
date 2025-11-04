#include "perfect_numbers.h"

namespace perfect_numbers
{
auto classify(integer_t number) -> classification
{
    if(number <= 0)
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    const uinteger_t unsigned_number{static_cast<uinteger_t>(number)};
    uinteger_t aliquot_sum{0U};

    for(uinteger_t divisor{1U}; (divisor <= (unsigned_number / divisor)); ++divisor)
    {
        if((unsigned_number % divisor) == 0U)
        {
            const uinteger_t paired_divisor{unsigned_number / divisor};

            if(divisor != unsigned_number)
            {
                aliquot_sum += divisor;
            }

            if((paired_divisor != divisor) && (paired_divisor != unsigned_number))
            {
                aliquot_sum += paired_divisor;
            }
        }
    }

    if(aliquot_sum == unsigned_number)
    {
        return classification::perfect;
    }

    if(aliquot_sum > unsigned_number)
    {
        return classification::abundant;
    }

    return classification::deficient;
}
}  // namespace perfect_numbers
