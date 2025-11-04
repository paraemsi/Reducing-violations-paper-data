#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

class all_your_base {
public:
    static std::vector<std::uint32_t> convert(std::uint32_t input_base, const std::vector<std::uint32_t>& digits, std::uint32_t output_base);
};

#endif // ALL_YOUR_BASE_H
