#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstddef>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& child) {
    // Split the diagram into two rows
    std::istringstream iss(diagram);
    std::string row1, row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // Remove any carriage return characters if present
    row1.erase(std::remove(row1.begin(), row1.end(), '\r'), row1.end());
    row2.erase(std::remove(row2.begin(), row2.end(), '\r'), row2.end());
    row1.erase(std::remove(row1.begin(), row1.end(), '\n'), row1.end());
    row2.erase(std::remove(row2.begin(), row2.end(), '\n'), row2.end());
    
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the child
    std::size_t index = 0;
    for (; index < children.size(); ++index) {
        if (children[index] == child) {
            break;
        }
    }
    // If child is not found, return empty vector
    if (index == children.size()) {
        return {};
    }
    
    // Get the positions for the child's plants
    std::size_t pos1 = 2 * index;
    std::size_t pos2 = (2 * index) + 1;
    
    // Ensure positions are within bounds
    if (pos2 >= row1.size() || pos2 >= row2.size()) {
        return {};
    }
    
    // Get plant codes from both rows
    char codes[4] = {
        row1[pos1], 
        row1[pos2], 
        row2[pos1], 
        row2[pos2]
    };
    
    // Convert codes to plant enums
    std::vector<Plants> child_plants;
    for (std::size_t j = 0; j < 4; ++j) {
        switch (codes[j]) {
            case 'G': child_plants.push_back(Plants::grass); break;
            case 'C': child_plants.push_back(Plants::clover); break;
            case 'R': child_plants.push_back(Plants::radishes); break;
            case 'V': child_plants.push_back(Plants::violets); break;
            default: break;
        }
    }
    
    return child_plants;
}

}  // namespace kindergarten_garden
