#include "perfect_numbers.h"
#include <numeric>
#include <cmath>

namespace perfect_numbers {

static int aliquot_sum(int n) {
    if (n <= 1) return 0;
    int sum = 1;
    int sqrt_n = static_cast<int>(std::sqrt(n));
    for (int i = 2; i <= sqrt_n; ++i) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i && other != n) {
                sum += other;
            }
        }
    }
    return sum;
}

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }
    int sum = aliquot_sum(n);
    if (sum == n) {
        return classification::perfect;
    } else if (sum > n) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
