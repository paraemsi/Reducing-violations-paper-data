#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(std::int64_t number) {
    if (number <= 0) {
        throw std::domain_error("Classification is only for positive integers");
    }
    
    if (number == 1) {
        return classification::deficient;
    }
    
    std::int64_t aliquot_sum = 1;
    std::int64_t sqrt_number = static_cast<std::int64_t>(std::sqrt(number));
    for (std::int64_t i = 2; i <= sqrt_number; ++i) {
        if ((number % i) == 0) {
            aliquot_sum += i;
            std::int64_t complement = number / i;
            if (complement != i) {
                aliquot_sum += complement;
            }
        }
    }
    
    if (aliquot_sum == number) {
        return classification::perfect;
    } else {
        if (aliquot_sum > number) {
            return classification::abundant;
        } else {
            return classification::deficient;
        }
    }
}

}  // namespace perfect_numbers
