#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    // Start with 1 for every n > 1; for n == 1 the aliquot sum is 0.
    int aliquot_sum = (n == 1) ? 0 : 1;

    // Sum the remaining proper divisors efficiently by iterating up to √n
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            aliquot_sum += i;
            int other = n / i;
            if (other != i) {          // avoid double-adding a square root divisor
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
