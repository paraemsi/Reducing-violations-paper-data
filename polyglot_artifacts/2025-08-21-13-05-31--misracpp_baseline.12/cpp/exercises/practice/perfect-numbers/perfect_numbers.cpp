#include "perfect_numbers.h"
#include <numeric>
#include <cmath>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only defined for positive integers.");
    }

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
    if (n == 1) sum = 0;

    if (sum == n) {
        return perfect;
    } else if (sum > n) {
        return abundant;
    } else {
        return deficient;
    }
}

}  // namespace perfect_numbers
