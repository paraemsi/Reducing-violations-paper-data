#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {
    
    classification classify(int number) {
        // Handle edge cases - throw exception for non-positive numbers
        if (number <= 0) {
            throw std::domain_error("Classification is only possible for positive integers");
        }
        
        // Calculate aliquot sum (sum of proper divisors)
        int aliquot_sum = 0;
        
        // Find all divisors up to sqrt(number) for efficiency
        for (int i = 1; i * i <= number; i++) {
            if (number % i == 0) {
                // i is a divisor
                if (i < number) {
                    aliquot_sum += i;
                }
                
                // number/i is also a divisor (if different from i)
                int other_divisor = number / i;
                if (other_divisor != i && other_divisor < number) {
                    aliquot_sum += other_divisor;
                }
            }
        }
        
        // Classify based on aliquot sum
        if (aliquot_sum == number) {
            return perfect;
        } else if (aliquot_sum > number) {
            return abundant;
        } else {
            return deficient;
        }
    }
    
}  // namespace perfect_numbers
