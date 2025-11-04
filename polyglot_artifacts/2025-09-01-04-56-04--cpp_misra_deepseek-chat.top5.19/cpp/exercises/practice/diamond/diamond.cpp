#include "diamond.h"
#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <iterator>

namespace diamond {

std::vector<std::string> rows(char letter) {
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Find the index of the letter using std::find and std::distance
    auto it = std::find(alphabet.begin(), alphabet.end(), letter);
    if (it == alphabet.end()) { 
        return std::vector<std::string>();
    }
    const int32_t index = static_cast<int32_t>(std::distance(alphabet.begin(), it));
    const int32_t size = 2 * index + 1;
    std::vector<std::string> result;
    
    // Generate each row
    for (int32_t i = 0; i <= index; i++) {
        std::string line(size, ' ');
        // Get the current letter by indexing into the alphabet
        // This is okay because we're not using the numerical value of the character
        const char current_letter = alphabet[static_cast<size_t>(i)];
        // Calculate positions
        const int32_t left_pos = index - i;
        const int32_t right_pos = index + i;
        // Assign the letters to their positions
        line[static_cast<size_t>(left_pos)] = current_letter;
        line[static_cast<size_t>(right_pos)] = current_letter;
        result.push_back(line);
    }
    
    // Add the bottom half in reverse order (excluding the middle row)
    for (int32_t i = index - 1; i >= 0; i--) {
        result.push_back(result[static_cast<size_t>(i)]);
    }
    
    return result;
}

}  // namespace diamond
