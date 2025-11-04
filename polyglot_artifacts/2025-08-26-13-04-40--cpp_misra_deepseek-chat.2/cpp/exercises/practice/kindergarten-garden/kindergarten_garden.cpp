#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cstdint>
#include <array>
#include <algorithm>

namespace kindergarten_garden {

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
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
    
    // Split the diagram into two rows, handling potential '\r'
    std::istringstream iss(diagram);
    std::string row1;
    std::string row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // Remove any carriage return characters
    row1.erase(std::remove(row1.begin(), row1.end(), '\r'), row1.end());
    row2.erase(std::remove(row2.begin(), row2.end(), '\r'), row2.end());
    
    // Calculate positions
    const std::int32_t start_pos = index * 2;
    
    // Map each plant code to the enum
    static const std::map<char, Plants> plant_map = {
        {'G', Plants::grass},
        {'C', Plants::clover},
        {'R', Plants::radishes},
        {'V', Plants::violets}
    };
    
    // Get plants from both rows
    std::array<Plants, 4> result;
    result[0] = plant_map.at(row1[static_cast<size_t>(start_pos)]);
    result[1] = plant_map.at(row1[static_cast<size_t>(start_pos) + 1]);
    result[2] = plant_map.at(row2[static_cast<size_t>(start_pos)]);
    result[3] = plant_map.at(row2[static_cast<size_t>(start_pos) + 1]);
    
    return result;
}

}  // namespace kindergarten_garden
