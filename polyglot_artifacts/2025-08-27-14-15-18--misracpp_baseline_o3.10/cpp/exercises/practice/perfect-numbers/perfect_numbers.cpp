#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error(
            "Classification is only possible for positive integers.");
    }

    // Special-case 1: its aliquot sum is 0.
    if (n == 1) {
        return classification::deficient;
    }

    int aliquot_sum = 1;           // 1 is a proper divisor of all n > 1
    for (int i = 2; i <= n / i; ++i) {
        if (n % i == 0) {
            aliquot_sum += i;
            int other = n / i;
            if (other != i) {      // avoid double-counting squares
                aliquot_sum += other;
            }
        }
    }

    if (aliquot_sum == n) {
        return classification::perfect;
    }
    if (aliquot_sum > n) {
        return classification::abundant;
    }
    return classification::deficient;
}

}  // namespace perfect_numbers
