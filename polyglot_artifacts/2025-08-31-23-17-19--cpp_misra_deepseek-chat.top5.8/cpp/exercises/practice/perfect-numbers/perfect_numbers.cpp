#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(number_t number) {
    if ((number <= 0)) {
        throw std::domain_error("Number must be positive");
    }
    
    if ((number == 1)) {
        return classification::deficient;
    }
    
    number_t sum = 1;
    // Cast to double to use with std::sqrt
    number_t root = static_cast<number_t>(std::sqrt(static_cast<double>(number)));
    for (number_t i = 2; i <= root; ++i) {
        if (((number % i) == 0)) {
            sum = (sum + i);
            number_t other_divisor = (number / i);
            if ((other_divisor != i)) {
                sum = (sum + other_divisor);
            }
        }
    }
    
    if ((sum == number)) {
        return classification::perfect;
    } else {
        if ((sum > number)) {
            return classification::abundant;
        } else {
            return classification::deficient;
        }
    }
}

}  // namespace perfect_numbers
