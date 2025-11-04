#include "perfect_numbers.h"
#include <cmath>

namespace perfect_numbers {

classification classify(number_t n)
{
    if (n == static_cast<number_t>(0U)) {
        // Zero is not classified by Nicomachus; treat as deficient
        return classification::deficient;
    }

    number_t sum = static_cast<number_t>(0U);

    for (number_t i = static_cast<number_t>(1U); (i <= (n / static_cast<number_t>(2U))); ++i) {
        if ((n % i) == static_cast<number_t>(0U)) {
            sum = static_cast<number_t>(sum + i);
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

std::string to_string(classification c)
{
    switch (c) {
        case classification::perfect:
            return "perfect";
        case classification::abundant:
            return "abundant";
        case classification::deficient:
            return "deficient";
        default:
            return "unknown";
    }
}

}  // namespace perfect_numbers
