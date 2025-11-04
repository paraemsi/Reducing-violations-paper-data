#include "perfect_numbers.h"
#include <cstdint>
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(std::int64_t number) {
    if (number <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    // Handle 1 as a special case (its only proper divisor is 0)
    if (number == 1) {
        return classification::deficient;
    }
    
    std::int64_t aliquot_sum = 1; // 1 is always a divisor
    std::int64_t sqrt_number = static_cast<std::int64_t>(std::sqrt(number));
    
    for (std::int64_t i = 2; i <= sqrt_number; i++) {
        if ((number % i) == 0) {
            aliquot_sum += i;
            std::int64_t complement = number / i;
            if (complement != i) {
                aliquot_sum += complement;
            }
        }
    }
    
    // Compare to classify
    if (aliquot_sum == number) {
        return classification::perfect;
    } else if (aliquot_sum > number) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
