#include "perfect_numbers.h"

namespace perfect_numbers {

static int aliquot_sum(int n) {
    int sum = 0;
    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0) {
            sum += i;
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
