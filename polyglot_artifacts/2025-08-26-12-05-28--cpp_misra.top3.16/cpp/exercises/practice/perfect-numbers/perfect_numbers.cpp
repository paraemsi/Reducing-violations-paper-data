#include "perfect_numbers.h"

namespace perfect_numbers {

static number_t aliquot_sum(number_t n)
{
    number_t sum = 0U;
    if(n <= 1U) {
        return 0U;
    }
    for(number_t i = 1U; (i <= (n / 2U)); ++i) {
        if((n % i) == 0U) {
            sum = (sum + i);
        }
    }
    return sum;
}

classification classify(number_t n)
{
    number_t sum = aliquot_sum(n);
    if(sum == n) {
        return perfect;
    } else if(sum > n) {
        return abundant;
    } else {
        return deficient;
    }
}

std::string to_string(classification c)
{
    switch(c) {
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
