#include "all_your_base.h"

namespace all_your_base {

Digits convert(std::uint32_t input_base, const Digits& input_digits, std::uint32_t output_base)
{
    // Validate bases
    if((input_base < static_cast<std::uint32_t>(2)) || (output_base < static_cast<std::uint32_t>(2)))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate digits and compute value
    std::uint64_t value = static_cast<std::uint64_t>(0);
    bool leading = true;
    for(Digit d : input_digits)
    {
        if((d >= input_base))
        {
            throw std::invalid_argument("Digit out of range for input base");
        }
        if(leading && (d == static_cast<Digit>(0)))
        {
            continue;
        }
        leading = false;
        value = (value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(d);
    }

    // Special case: input is all zeros or empty
    if(leading)
    {
        return Digits{};
    }

    // Convert value to output_base
    Digits output_digits;
    while(value > static_cast<std::uint64_t>(0))
    {
        output_digits.insert(output_digits.begin(), static_cast<Digit>(value % static_cast<std::uint64_t>(output_base)));
        value = value / static_cast<std::uint64_t>(output_base);
    }

    return output_digits;
}

}  // namespace all_your_base
