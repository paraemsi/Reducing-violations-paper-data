#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("classification is only defined for positive integers");
    }
    if (n == 1) {
        return classification::deficient;
    }

    int sum = 1;
    for (int i = 2; i <= n / i; ++i) {
        if (n % i == 0) {
            int j = n / i;
            sum += i;
            if (j != i) {
                sum += j;
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
