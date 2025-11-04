#include "perfect_numbers.h"
#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

classification classify(std::int64_t number) {
    // Numbers less than or equal to 0 are not positive integers
    if (number <= 0) {
        throw std::domain_error("Classification is only possible for positive integers");
    }
    
    // 1 is deficient (aliquot sum is 0)
    if (number == 1) {
        return classification::deficient;
    }
    
    // Calculate aliquot sum (sum of proper divisors)
    std::int64_t aliquot_sum = 0;
    
    // Find all divisors up to sqrt(number)
    // We check up to number/2 since no factor can be greater than number/2
    std::int64_t limit = number / 2;
    
    for (std::int64_t i = 1; i <= limit; ++i) {
        if ((number % i) == 0) {
            aliquot_sum = aliquot_sum + i;
        }
    }
    
    // Classify based on aliquot sum
    if (aliquot_sum == number) {
        return classification::perfect;
    } else if (aliquot_sum > number) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
