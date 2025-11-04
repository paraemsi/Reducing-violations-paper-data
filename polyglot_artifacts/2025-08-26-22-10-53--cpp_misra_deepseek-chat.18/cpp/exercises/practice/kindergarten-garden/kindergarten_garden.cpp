#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <cstdint>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred", 
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    std::int32_t index = 0;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(children.size()); i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into two lines
    std::size_t newline_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);
    
    // Get the plants for the child at index
    std::vector<Plants> result;
    
    // Calculate positions
    std::int32_t start_pos = 2 * index;
    
    // Helper function to convert character to Plants enum
    auto charToPlant = [](char c) -> Plants {
        switch (c) {
            case 'G': return Plants::grass;
            case 'C': return Plants::clover;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::grass; // Should not happen according to the problem
        }
    };
    
    // Add plants in order: first row left, first row right, second row left, second row right
    result.push_back(charToPlant(row1[start_pos]));
    result.push_back(charToPlant(row1[start_pos + 1]));
    result.push_back(charToPlant(row2[start_pos]));
    result.push_back(charToPlant(row2[start_pos + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
