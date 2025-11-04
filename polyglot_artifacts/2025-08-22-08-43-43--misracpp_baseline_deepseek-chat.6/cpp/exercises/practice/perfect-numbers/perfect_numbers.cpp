#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int num) {
    if (num <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    int sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    
    if (sum == num) {
        return perfect;
    } else if (sum > num) {
        return abundant;
    } else {
        return deficient;
    }
}

}  // namespace perfect_numbers
