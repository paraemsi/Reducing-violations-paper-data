#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

classification classify(std::uint32_t n)
{
    if (n == 0U) {
        throw std::domain_error("Classification is not defined for zero.");
    }

    if (n == 1U) {
        return classification::deficient;
    }

    std::uint32_t aliquot_sum = 1U;

    for (std::uint32_t i = 2U; i <= (n / i); ++i) {
        if ((n % i) == 0U) {
            aliquot_sum += i;

            const std::uint32_t complement = n / i;
            if (complement != i) {
                aliquot_sum += complement;
            }
        }
    }

    if (aliquot_sum == n) {
        return classification::perfect;
    } else if (aliquot_sum > n) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

classification classify(std::int32_t n)
{
    /* Reject non-positive values per specification. */
    if (n <= 0) {
        throw std::domain_error("Classification is not defined for non-positive integers.");
    }

    /*  Positive signed value – safe to convert;
     *  explicit cast documents the intended conversion.
     */
    return classify(static_cast<std::uint32_t>(n));
}

}  // namespace perfect_numbers
