#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

    // Converts a number represented as a vector of digits in base 'from_base'
    // to a vector of digits in base 'to_base'.
    // Throws std::invalid_argument on invalid input.
    std::vector<unsigned int> convert(
        unsigned int from_base,
        std::vector<unsigned int> const& digits,
        unsigned int to_base
    );

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
