#include "perfect_numbers.h"

namespace perfect_numbers {

static int aliquot_sum(int n) {
    if (n <= 1) {
        return 0;
    }
    int sum = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            int d = n / i;
            if (d != i) {
                sum += d;
            }
        }
    }
    return sum;
}

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("classification is only possible for positive integers");
    }
    const int sum = aliquot_sum(n);
    if (sum == n) {
        return classification::perfect;
    }
    if (sum > n) {
        return classification::abundant;
    }
    return classification::deficient;
}

}  // namespace perfect_numbers
