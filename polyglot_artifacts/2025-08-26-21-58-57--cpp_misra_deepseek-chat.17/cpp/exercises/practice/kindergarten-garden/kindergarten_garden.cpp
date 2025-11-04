#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace kindergarten_garden {

std::vector<Plant> plants(const std::string& diagram, const std::string& child) {
    // Split the diagram into two rows
    std::istringstream iss(diagram);
    std::string row1, row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // List of children in fixed alphabetical order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred", 
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the child
    auto it = std::find(children.begin(), children.end(), child);
    if (it == children.end()) {
        return {};
    }
    size_t index = it - children.begin();
    
    // Calculate start position in each row
    size_t start = 2 * index;
    
    // Get the plants
    char plant1_char = row1[start];
    char plant2_char = row1[start + 1];
    char plant3_char = row2[start];
    char plant4_char = row2[start + 1];
    
    // Helper lambda to convert char to plant enum
    auto char_to_plant = [](char c) -> Plant {
        switch (c) {
            case 'G': return Plant::grass;
            case 'C': return Plant::clover;
            case 'R': return Plant::radishes;
            case 'V': return Plant::violets;
            default: return Plant::grass; // Should not happen according to the problem
        }
    };
    
    return {
        char_to_plant(plant1_char),
        char_to_plant(plant2_char),
        char_to_plant(plant3_char),
        char_to_plant(plant4_char)
    };
}

}  // namespace kindergarten_garden
