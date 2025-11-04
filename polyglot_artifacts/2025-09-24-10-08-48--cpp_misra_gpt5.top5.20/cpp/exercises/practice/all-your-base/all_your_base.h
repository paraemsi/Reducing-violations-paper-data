#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

 // Adapter signature to match expected external API; internally we use fixed-width types.
std::vector<unsigned int> convert(unsigned int in_base, const std::vector<unsigned int>& in_digits, unsigned int out_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
