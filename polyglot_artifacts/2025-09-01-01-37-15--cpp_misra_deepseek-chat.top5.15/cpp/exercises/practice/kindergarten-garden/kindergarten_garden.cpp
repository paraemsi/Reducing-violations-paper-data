#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& child) {
    // Split the diagram into two lines
    std::istringstream iss(diagram);
    std::string row1;
    std::string row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // The list of children in order
    const std::vector<std::string> children_list = {
        "Alice", "Bob", "Charlie", "David", 
        "Eve", "Fred", "Ginny", "Harriet", 
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the child
    std::int32_t child_index = 0;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(children_list.size()); i++) {
        if (children_list[i] == child) {
            child_index = i;
            break;
        }
    }
    
    // Each child has 2 plants per row, so their plants are at positions 2*index and 2*index +1 in each row
    std::int32_t start_index = 2 * child_index;
    
    // Get the plant codes
    std::vector<Plants> result;
    
    // Helper lambda to convert code to Plants enum
    auto code_to_plant = [](char code) -> Plants {
        switch (code) {
            case 'R': return Plants::radishes;
            case 'C': return Plants::clover;
            case 'G': return Plants::grass;
            case 'V': return Plants::violets;
            default: return Plants::radishes; // Should not happen according to the problem
        }
    };
    
    // Process first row
    result.push_back(code_to_plant(row1[start_index]));
    result.push_back(code_to_plant(row1[start_index + 1]));
    
    // Process second row
    result.push_back(code_to_plant(row2[start_index]));
    result.push_back(code_to_plant(row2[start_index + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
