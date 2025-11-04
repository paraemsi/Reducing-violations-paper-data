#include "perfect_numbers.h"
#include <numeric>
#include <cmath>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    int aliquot_sum = 1;
    int sqrt_n = static_cast<int>(std::sqrt(n));
    for (int i = 2; i <= sqrt_n; ++i) {
        if (n % i == 0) {
            aliquot_sum += i;
            int other = n / i;
            if (other != i && other != n) {
                aliquot_sum += other;
            }
        }
    }
    if (n == 1) {
        aliquot_sum = 0;
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
