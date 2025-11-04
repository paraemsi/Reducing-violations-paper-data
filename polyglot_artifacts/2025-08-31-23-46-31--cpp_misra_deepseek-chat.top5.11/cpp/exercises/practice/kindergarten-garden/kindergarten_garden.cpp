#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    std::int32_t index = 0;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(children.size()); i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into two rows
    // Find the newline position to split the string
    std::size_t newline_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);
    
    // Calculate the starting position for the student's plants
    std::int32_t start_pos = 2 * index;
    
    std::vector<Plants> result;
    
    // Helper lambda to convert char to Plants
    auto to_plant = [](char c) -> Plants {
        switch (c) {
            case 'G': return Plants::grass;
            case 'C': return Plants::clover;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::grass;
        }
    };
    
    // Get plants from both rows
    result.push_back(to_plant(row1[start_pos]));
    result.push_back(to_plant(row1[start_pos + 1]));
    result.push_back(to_plant(row2[start_pos]));
    result.push_back(to_plant(row2[start_pos + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
