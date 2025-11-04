#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& child) {
    // Split into exactly two rows
    size_t newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        return {};
    }
    
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);
    
    // Ensure both rows have the same length and are non-empty
    if (row1.empty() || row2.empty() || row1.size() != row2.size()) {
        return {};
    }
    
    // List of children in exact order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the child
    int index = -1;
    for (size_t i = 0; i < children.size(); ++i) {
        if (children[i] == child) {
            index = static_cast<int>(i);
            break;
        }
    }
    if (index == -1) {
        return {};
    }
    
    // Each child has 2 cups per row, so calculate positions
    size_t start = 2 * index;
    if (start + 1 >= row1.size()) {
        return {};
    }
    
    // Get the plants
    std::vector<Plants> result;
    
    // Helper to convert character to plant
    auto to_plant = [](char c) {
        switch (c) {
            case 'C': return Plants::clover;
            case 'G': return Plants::grass;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::grass;
        }
    };
    
    // Add plants from first row
    result.push_back(to_plant(row1[start]));
    result.push_back(to_plant(row1[start + 1]));
    // Add plants from second row
    result.push_back(to_plant(row2[start]));
    result.push_back(to_plant(row2[start + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
