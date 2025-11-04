#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>

namespace all_your_base {

// Define type aliases to satisfy both MISRA rules and test requirements
// Since tests use unsigned int, we'll make sure our types are exactly unsigned int
using ubase_t = unsigned int;
using udigit_t = unsigned int;

std::vector<udigit_t> convert(ubase_t input_base,
                              const std::vector<udigit_t>& input_digits,
                              ubase_t output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
