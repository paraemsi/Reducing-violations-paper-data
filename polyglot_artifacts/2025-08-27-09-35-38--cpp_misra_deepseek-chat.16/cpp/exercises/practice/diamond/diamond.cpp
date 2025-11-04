#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return std::vector<std::string>{"A"};
    }
    
    // Convert to an appropriate integer type to avoid signedness issues
    const std::uint32_t n = static_cast<std::uint32_t>(letter - 'A');
    const std::uint32_t size = (2U * n) + 1U;
    std::vector<std::string> result;
    
    // Build the top half including the middle
    for (std::uint32_t i = 0U; i <= n; i++) {
        std::string row(size, ' ');
        const char current_char = static_cast<char>('A' + i);
        
        // Set the appropriate positions
        const std::uint32_t left_pos = n - i;
        const std::uint32_t right_pos = n + i;
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        
        result.push_back(row);
    }
    
    // Build the bottom half by mirroring the top (excluding the middle)
    // To loop from n-1 down to 0 using unsigned integers
    for (std::uint32_t i = n - 1U; ; i--) {
        result.push_back(result[i]);
        if (i == 0U) {
            break;
        }
    }
    
    return result;
}

}  // namespace diamond
