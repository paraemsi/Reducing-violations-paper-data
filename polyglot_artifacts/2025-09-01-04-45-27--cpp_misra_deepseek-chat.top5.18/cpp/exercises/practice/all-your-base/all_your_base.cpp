#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<digit_t> convert(base_t input_base, 
                             const std::vector<digit_t>& input_digits, 
                             base_t output_base) {
    // Check for valid bases
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    
    // Handle empty input
    if (input_digits.empty()) {
        return std::vector<digit_t>();
    }
    
    // Check all digits are valid for the input base
    for (const auto& digit : input_digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
    
    // Define a type for the intermediate number
    struct NumberType {
        using type = std::uint64_t;
    };
    using number_t = NumberType::type;
    
    // Convert the number to a value
    number_t number = 0;
    for (const auto& digit : input_digits) {
        number = (number * static_cast<number_t>(input_base)) + static_cast<number_t>(digit);
    }
    
    // Convert to output base
    std::vector<digit_t> output_digits;
    // Handle the case when number is 0 - according to tests, return empty vector
    if (number == 0) {
        // Return empty vector, not {0}
        return std::vector<digit_t>();
    }
    
    while (number > 0) {
        output_digits.insert(output_digits.begin(), 
                             static_cast<digit_t>(number % static_cast<number_t>(output_base)));
        number /= static_cast<number_t>(output_base);
    }
    
    return output_digits;
}

}  // namespace all_your_base
