#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(number_t number) {
    if (number <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    // Handle 1 as a special case (its only proper divisor is 0)
    if (number == 1) {
        return classification::deficient;
    }
    
    number_t sum = 0;
    for (number_t i = 1; i <= (number / 2); i++) {
        if ((number % i) == 0) {
            sum += i;
        }
    }
    
    if (sum == number) {
        return classification::perfect;
    } else {
        if (sum > number) {
            return classification::abundant;
        } else {
            return classification::deficient;
        }
    }
}

}  // namespace perfect_numbers
