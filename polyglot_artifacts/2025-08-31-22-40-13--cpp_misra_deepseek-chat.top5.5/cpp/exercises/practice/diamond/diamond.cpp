#include "diamond.h"
#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    // Find the index using a lookup table
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::int32_t max_index = 0;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(alphabet.size()); i++) {
        if (alphabet[static_cast<std::size_t>(i)] == letter) {
            max_index = i;
            break;
        }
    }
    
    const std::int32_t size = (2 * max_index) + 1;
    std::vector<std::string> diamond;
    
    // Generate top half including the middle
    for (std::int32_t i = 0; i <= max_index; i++) {
        std::string row(size, ' ');
        const char current_char = alphabet[static_cast<std::size_t>(i)];
        const std::int32_t left_pos = max_index - i;
        const std::int32_t right_pos = max_index + i;
        row[static_cast<std::size_t>(left_pos)] = current_char;
        row[static_cast<std::size_t>(right_pos)] = current_char;
        diamond.push_back(row);
    }
    
    // Generate bottom half by mirroring the top half (excluding the middle)
    for (std::int32_t i = (max_index - 1); i >= 0; i--) {
        diamond.push_back(diamond[static_cast<std::size_t>(i)]);
    }
    
    return diamond;
}

}  // namespace diamond
