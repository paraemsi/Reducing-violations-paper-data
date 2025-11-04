#include "perfect_numbers.h"
#include <cmath>
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Only positive integers may be classified");
    }

    // Special-case 1: its aliquot sum is 0, therefore deficient.
    if (n == 1) {
        return classification::deficient;
    }

    int aliquot_sum = 1;                    // 1 is a proper divisor of every n > 1
    int root        = static_cast<int>(std::sqrt(n));

    for (int i = 2; i <= root; ++i) {
        if (n % i == 0) {
            aliquot_sum += i;
            int other = n / i;
            if (other != i) {               // avoid double-counting squares
                aliquot_sum += other;
            }
        }
    }

    if (aliquot_sum == n) {
        return classification::perfect;
    }
    return (aliquot_sum > n) ? classification::abundant
                             : classification::deficient;
}

}  // namespace perfect_numbers
