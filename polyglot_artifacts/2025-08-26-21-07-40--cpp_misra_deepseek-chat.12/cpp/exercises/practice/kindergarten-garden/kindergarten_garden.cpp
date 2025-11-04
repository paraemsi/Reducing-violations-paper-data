#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <sstream>
#include <algorithm>

namespace kindergarten_garden {

std::array<Plants, 4> plants(const std::string& diagram, const std::string& child) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the child
    auto it = std::find(children.begin(), children.end(), child);
    if (it == children.end()) {
        // According to the instructions, this should not happen
        return {};
    }
    std::int32_t index = static_cast<std::int32_t>(it - children.begin());
    
    // Split the diagram into exactly two lines
    std::size_t newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        // Handle error - the diagram should have two lines
        return {};
    }
    
    std::string line1 = diagram.substr(0, newline_pos);
    std::string line2 = diagram.substr(newline_pos + 1);
    
    // Make sure both lines have the same length and are not empty
    if (line1.empty() || line2.empty() || line1.size() != line2.size()) {
        return {};
    }
    
    // Get the plants for the child
    std::array<Plants, 4> result;
    
    // Calculate positions
    std::int32_t pos1 = 2 * index;
    std::int32_t pos2 = 2 * index + 1;
    
    // Check if positions are valid
    if (pos1 >= static_cast<std::int32_t>(line1.size()) || pos2 >= static_cast<std::int32_t>(line1.size())) {
        return {};
    }
    
    // Convert each character to plant enum
    auto convertPlant = [](char c) -> Plants {
        switch (c) {
            case 'G': return Plants::grass;
            case 'C': return Plants::clover;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::grass;
        }
    };
    
    // Add plants from first row
    result[0] = convertPlant(line1[pos1]);
    result[1] = convertPlant(line1[pos2]);
    // Add plants from second row
    result[2] = convertPlant(line2[pos1]);
    result[3] = convertPlant(line2[pos2]);
    
    return result;
}

}  // namespace kindergarten_garden
