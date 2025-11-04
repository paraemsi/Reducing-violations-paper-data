#include "perfect_numbers.h"
#include <ostream>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for positive integers");
    }
    if (n == 1) {
        return classification::deficient;
    }

    int sum = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i) {
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

std::ostream& operator<<(std::ostream& os, classification c) {
    switch (c) {
        case classification::perfect:
            os << "perfect";
            break;
        case classification::abundant:
            os << "abundant";
            break;
        case classification::deficient:
            os << "deficient";
            break;
    }
    return os;
}

}  // namespace perfect_numbers
