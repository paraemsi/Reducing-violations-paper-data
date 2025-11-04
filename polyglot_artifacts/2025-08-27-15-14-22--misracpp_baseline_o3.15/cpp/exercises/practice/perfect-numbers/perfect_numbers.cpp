#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(long long n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    if (n == 1) {
        return classification::deficient;
    }

    long long aliquot_sum = 1;                    // 1 is a factor of every n > 1
    long long sqrt_n = static_cast<long long>(std::sqrt(n));

    for (long long i = 2; i <= sqrt_n; ++i) {
        if (n % i == 0) {
            aliquot_sum += i;
            long long other = n / i;
            if (other != i) {                     // avoid double-counting squares
                aliquot_sum += other;
            }
        }
    }

    if (aliquot_sum == n) {
        return classification::perfect;
    } else if (aliquot_sum > n) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
