#include "kindergarten_garden.h"
#include <string>
#include <vector>
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
    
    // Split the diagram into two rows
    // The diagram is a string that may contain newlines
    std::istringstream iss(diagram);
    std::string row1, row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // Each child has 2 plants per row, so calculate the starting index
    std::int32_t start_pos = index * 2;
    
    // Map characters to Plants enum
    std::map<char, Plants> plant_map = {
        {'G', Plants::grass},
        {'C', Plants::clover},
        {'R', Plants::radishes},
        {'V', Plants::violets}
    };
    
    // Get the plants for the child
    std::vector<Plants> result;
    result.push_back(plant_map[row1[start_pos]]);
    result.push_back(plant_map[row1[start_pos + 1]]);
    result.push_back(plant_map[row2[start_pos]]);
    result.push_back(plant_map[row2[start_pos + 1]]);
    
    return result;
}

}  // namespace kindergarten_garden
