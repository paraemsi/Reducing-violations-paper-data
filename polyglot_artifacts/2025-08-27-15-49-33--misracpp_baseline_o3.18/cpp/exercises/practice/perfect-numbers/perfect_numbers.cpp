#include "perfect_numbers.h"

#include <cmath>
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error(
            "Classification is only possible for positive integers.");
    }

    // 1 is a special case: it has no proper divisors other than itself.
    if (n == 1) {
        return classification::deficient;
    }

    int sum{1};  // 1 is a proper divisor of every n > 1
    int limit = static_cast<int>(std::sqrt(n));

    for (int i = 2; i <= limit; ++i) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i) {  // avoid adding the square root twice for perfect squares
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
