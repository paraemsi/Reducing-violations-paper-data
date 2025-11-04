#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <array>
#include <cstdint>
#include <cstddef>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& child) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred", 
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the child
    std::int32_t index = 0;
    for (std::size_t i = 0; i < children.size(); i++) {
        if (children[i] == child) {
            index = static_cast<std::int32_t>(i);
            break;
        }
    }
    
    // Split the diagram into two rows
    std::size_t split_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, split_pos);
    std::string row2 = diagram.substr(split_pos + 1);
    
    // Get the plants for the child
    std::vector<Plants> result;
    
    // For each plant code, map to enum
    std::size_t start = 2 * static_cast<std::size_t>(index);
    // Ensure we don't go out of bounds
    char plant1 = row1.at(start);
    char plant2 = row1.at(start + 1);
    char plant3 = row2.at(start);
    char plant4 = row2.at(start + 1);
    
    // Helper lambda to convert code to plant enum
    auto code_to_plant = [](char code) -> Plants {
        switch (code) {
            case 'G': return Plants::grass;
            case 'C': return Plants::clover;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::grass; // Should not happen according to the problem
        }
    };
    
    result.push_back(code_to_plant(plant1));
    result.push_back(code_to_plant(plant2));
    result.push_back(code_to_plant(plant3));
    result.push_back(code_to_plant(plant4));
    
    return result;
}

}  // namespace kindergarten_garden
