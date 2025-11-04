#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int num) {
    if (num <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    // Handle 1 separately
    if (num == 1) {
        return classification::deficient;
    }
    
    int sum = 1; // 1 is always a proper divisor
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            int other = num / i;
            if (i == other) {
                sum += i;
            } else {
                sum += i + other;
            }
        }
    }
    
    // Classify based on the aliquot sum
    if (sum == num) {
        return classification::perfect;
    } else if (sum > num) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
