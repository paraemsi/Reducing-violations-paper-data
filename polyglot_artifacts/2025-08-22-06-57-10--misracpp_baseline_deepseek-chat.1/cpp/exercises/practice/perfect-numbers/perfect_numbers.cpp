#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int num) {
    if (num <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    int aliquot_sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            aliquot_sum += i;
        }
    }
    
    if (aliquot_sum == num) {
        return classification::perfect;
    } else if (aliquot_sum > num) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
