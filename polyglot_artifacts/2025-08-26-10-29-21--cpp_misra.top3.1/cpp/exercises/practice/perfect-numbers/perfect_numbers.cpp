#include "perfect_numbers.h"
#include <cmath>

namespace perfect_numbers {

classification classify(number_t n)
{
    if (n == static_cast<number_t>(0U)) {
        // 0 is not classified by Nicomachus, but we must return something.
        return deficient;
    }

    number_t sum = static_cast<number_t>(0U);

    for (number_t i = static_cast<number_t>(1U); (i <= (n / static_cast<number_t>(2U))); ++i) {
        if ((n % i) == static_cast<number_t>(0U)) {
            sum = static_cast<number_t>(sum + i);
        }
    }

    if (sum == n) {
        return perfect;
    } else if (sum > n) {
        return abundant;
    } else {
        return deficient;
    }
}

std::string to_string(classification c)
{
    switch (c) {
        case perfect:
            return "perfect";
        case abundant:
            return "abundant";
        case deficient:
            return "deficient";
        default:
            return "unknown";
    }
}

}  // namespace perfect_numbers
