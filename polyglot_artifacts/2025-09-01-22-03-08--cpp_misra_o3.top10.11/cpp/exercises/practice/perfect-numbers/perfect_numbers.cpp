#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int32_t number) -> classification {
    if(number <= 0) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    const std::uint32_t n = static_cast<std::uint32_t>(number);

    std::uint64_t aliquot_sum = 0U;

    if(n > 1U) {
        aliquot_sum = 1U;

        for(std::uint32_t factor = 2U; factor <= (n / factor); ++factor) {
            if((n % factor) == 0U) {
                aliquot_sum += static_cast<std::uint64_t>(factor);
                const std::uint32_t complement = n / factor;
                if(complement != factor) {
                    aliquot_sum += static_cast<std::uint64_t>(complement);
                }
            }
        }
    }

    const std::uint64_t n64 = static_cast<std::uint64_t>(n);

    if(aliquot_sum == n64) {
        return classification::perfect;
    }
    if(aliquot_sum > n64) {
        return classification::abundant;
    }
    return classification::deficient;
}

auto classify(std::uint32_t number) -> classification {
    /* Delegate to the signed overload (value is non-negative). */
    return classify(static_cast<std::int32_t>(number));
}


}  // namespace perfect_numbers
