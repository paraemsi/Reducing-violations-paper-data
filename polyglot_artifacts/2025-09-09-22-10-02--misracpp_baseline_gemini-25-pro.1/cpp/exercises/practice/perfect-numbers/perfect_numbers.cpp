#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

classification classify(int number) {
    if (number <= 0) {
        throw std::domain_error(
            "Classification is only possible for positive integers.");
    }

    int aliquot_sum = 0;
    for (int i = 1; i <= number / 2; ++i) {
        if (number % i == 0) {
            aliquot_sum += i;
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
