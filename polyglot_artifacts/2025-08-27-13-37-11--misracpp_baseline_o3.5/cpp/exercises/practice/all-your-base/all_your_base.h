#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

    // Convert `digits` expressed in `from_base` into a vector of digits
    // expressed in `to_base`.  Most-significant digit first.
    // Throws std::invalid_argument on invalid input.
    [[nodiscard]] std::vector<int> convert(int from_base,
                                           const std::vector<int>& digits,
                                           int to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
