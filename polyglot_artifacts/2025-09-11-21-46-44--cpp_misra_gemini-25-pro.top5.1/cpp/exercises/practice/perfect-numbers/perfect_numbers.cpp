#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(std::int32_t number) {
    if (number < 1) {
        throw std::domain_error("Classification is only for positive integers.");
    }

    if (number == 1) {
        return classification::deficient;
    }

    std::int32_t aliquot_sum = 1;
    for (std::int32_t i = 2; i <= (number / i); ++i) {
        if ((number % i) == 0) {
            aliquot_sum += i;
            const std::int32_t d = number / i;
            if (d != i) {
                aliquot_sum += d;
            }
        }
    }

    if (aliquot_sum == number) {
        return classification::perfect;
    } else if (aliquot_sum > number) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
