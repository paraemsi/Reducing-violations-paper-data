#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <cstdint>
#include <sstream>
#include <algorithm>
#include <array>

namespace kindergarten_garden {

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    std::int32_t index = static_cast<std::int32_t>(it - children.begin());
    
    // Split the diagram into two rows
    std::istringstream iss(diagram);
    std::string first_row;
    std::string second_row;
    std::getline(iss, first_row);
    std::getline(iss, second_row);
    
    // Get the plants for the child
    std::array<Plants, 4> result;
    
    // First row plants
    std::int32_t start = 2 * index;
    
    // Helper function to convert character to Plants enum
    auto char_to_plant = [](char c) -> Plants {
        switch (c) {
            case 'C': return Plants::clover;
            case 'G': return Plants::grass;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::clover;
        }
    };
    
    result[0] = char_to_plant(first_row[start]);
    result[1] = char_to_plant(first_row[start + 1]);
    result[2] = char_to_plant(second_row[start]);
    result[3] = char_to_plant(second_row[start + 1]);
    
    return result;
}

}  // namespace kindergarten_garden
