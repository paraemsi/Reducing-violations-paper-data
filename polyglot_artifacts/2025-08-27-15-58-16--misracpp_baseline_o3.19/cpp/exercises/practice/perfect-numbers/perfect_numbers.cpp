#include "perfect_numbers.h"
#include <cmath>
#include <stdexcept>

namespace perfect_numbers {

classification classify(int number) {
    if (number <= 0) {
        throw std::domain_error{"Classification is only defined for positive integers."};
    }
    if (number == 1) {
        return classification::deficient;
    }

    int aliquot_sum = 1;
    int limit = static_cast<int>(std::sqrt(number));
    for (int i = 2; i <= limit; ++i) {
        if (number % i == 0) {
            aliquot_sum += i;
            int complement = number / i;
            if (complement != i) {
                aliquot_sum += complement;
            }
        }
    }

    if (aliquot_sum == number) {
        return classification::perfect;
    }
    if (aliquot_sum > number) {
        return classification::abundant;
    }
    return classification::deficient;
}

}  // namespace perfect_numbers
