#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <array>
#include <cstdint>
#include <sstream>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& child) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the child
    std::int32_t index = -1;
    for (std::int32_t i = 0; i < 12; i++) {
        if (children[i] == child) {
            index = i;
            break;
        }
    }
    
    // If child not found, return empty vector
    if (index == -1) {
        return {};
    }
    
    // Split the diagram into lines
    std::vector<std::string> rows;
    std::istringstream iss(diagram);
    std::string line;
    while (std::getline(iss, line)) {
        rows.push_back(line);
    }
    
    // Make sure we have exactly two rows
    if (rows.size() < 2) {
        return {};
    }
    
    const std::string& row1 = rows[0];
    const std::string& row2 = rows[1];
    
    // Get the starting position for the child's plants
    std::int32_t start_pos = index * 2;
    
    // Check if positions are valid
    if ((start_pos + 1) >= static_cast<std::int32_t>(row1.length()) || 
        (start_pos + 1) >= static_cast<std::int32_t>(row2.length())) {
        return {};
    }
    
    // Get the plants
    std::vector<Plants> result;
    
    // Process first row
    for (std::int32_t i = 0; i < 2; i++) {
        char plant_code = row1[start_pos + i];
        switch (plant_code) {
            case 'G': { result.push_back(Plants::grass); break; }
            case 'C': { result.push_back(Plants::clover); break; }
            case 'R': { result.push_back(Plants::radishes); break; }
            case 'V': { result.push_back(Plants::violets); break; }
            default: { break; }
        }
    }
    
    // Process second row
    for (std::int32_t i = 0; i < 2; i++) {
        char plant_code = row2[start_pos + i];
        switch (plant_code) {
            case 'G': { result.push_back(Plants::grass); break; }
            case 'C': { result.push_back(Plants::clover); break; }
            case 'R': { result.push_back(Plants::radishes); break; }
            case 'V': { result.push_back(Plants::violets); break; }
            default: { break; }
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
