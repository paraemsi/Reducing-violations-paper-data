#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(std::int64_t number) {
    if (number <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    // Handle 1 separately
    if (number == 1) {
        return classification::deficient;
    }
    
    std::int64_t aliquot_sum = 0;
    for (std::int64_t i = 1; i <= static_cast<std::int64_t>(std::sqrt(number)); ++i) {
        if ((number % i) == 0) {
            // Add the divisor
            aliquot_sum += i;
            // Add the complement if it's different and not the number itself
            std::int64_t complement = number / i;
            if (complement != i && complement != number) {
                aliquot_sum += complement;
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
