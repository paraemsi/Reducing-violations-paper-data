#include "perfect_numbers.h"
#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

classification classify(int64_t n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }
    if (n == 1) {
        return classification::deficient;
    }

    std::int64_t sum = 1;  // 1 is a proper divisor of every n > 1
    for (std::int64_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {           // add the complementary divisor
                sum += n / i;
            }
        }
    }

    if (sum == n) {
        return classification::perfect;
    } else if (sum > n) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
