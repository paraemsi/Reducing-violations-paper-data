#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

int aliquot_sum(int n) {
    if (n <= 1) return 0;
    int sum = 1;  // 1 is always a divisor
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) sum += n / i;
        }
    }
    return sum;
}

classification classify(int number) {
    if (number <= 0) {
        throw std::invalid_argument("Number must be positive");
    }
    int sum = aliquot_sum(number);
    if (sum == number) return classification::perfect;
    if (sum > number) return classification::abundant;
    return classification::deficient;
}

}  // namespace perfect_numbers
