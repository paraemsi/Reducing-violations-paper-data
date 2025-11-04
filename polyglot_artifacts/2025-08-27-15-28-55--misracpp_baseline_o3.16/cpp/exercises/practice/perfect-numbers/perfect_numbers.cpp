#include "perfect_numbers.h"
#include <cmath>
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Only positive integers can be classified.");
    }
    if (n == 1) {
        return classification::deficient;
    }

    int sum = 1;  // 1 is a proper divisor of every integer > 1
    int root = static_cast<int>(std::sqrt(n));
    for (int i = 2; i <= root; ++i) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i) {       // avoid double-counting squares
                sum += other;
            }
        }
    }

    if (sum == n) {
        return classification::perfect;
    }
    if (sum > n) {
        return classification::abundant;
    }
    return classification::deficient;
}

}  // namespace perfect_numbers
