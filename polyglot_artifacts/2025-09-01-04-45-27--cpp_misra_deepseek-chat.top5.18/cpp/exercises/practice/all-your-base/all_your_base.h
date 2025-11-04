#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

// Define type aliases that use fixed-width types internally
struct DigitType {
    using type = std::uint32_t;
};
struct BaseType {
    using type = std::uint32_t;
};

using digit_t = DigitType::type;
using base_t = BaseType::type;

std::vector<digit_t> convert(base_t input_base, 
                             const std::vector<digit_t>& input_digits, 
                             base_t output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
