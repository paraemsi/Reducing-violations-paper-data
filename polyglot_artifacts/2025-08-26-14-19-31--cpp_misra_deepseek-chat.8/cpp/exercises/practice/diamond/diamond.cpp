#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> diamond;
    
    if (letter == 'A') {
        diamond.push_back("A");
        return diamond;
    }
    
    const std::int32_t n = static_cast<std::int32_t>(letter - 'A');
    const std::int32_t size = (2 * n) + 1;
    
    // Generate each line
    for (std::int32_t i = 0; i <= n; i++) {
        std::string line(static_cast<size_t>(size), ' ');
        const char current_char = static_cast<char>('A' + i);
        const std::int32_t left = n - i;
        const std::int32_t right = n + i;
        line[static_cast<size_t>(left)] = current_char;
        line[static_cast<size_t>(right)] = current_char;
        diamond.push_back(line);
    }
    
    // Add the bottom part by mirroring
    for (std::int32_t i = n - 1; i >= 0; i--) {
        diamond.push_back(diamond[static_cast<size_t>(i)]);
    }
    
    return diamond;
}

}  // namespace diamond
