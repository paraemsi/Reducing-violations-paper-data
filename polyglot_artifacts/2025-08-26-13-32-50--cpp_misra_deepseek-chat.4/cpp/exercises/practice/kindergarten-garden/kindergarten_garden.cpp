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
        "Alice", "Bob", "Charlie", "David", 
        "Eve", "Fred", "Ginny", "Harriet", 
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    std::int32_t index = -1;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(children.size()); i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into two rows
    // Find the newline position
    std::size_t newline_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);
    
    // Determine the plant codes for the child
    std::int32_t pos = 2 * index;
    char c1 = row1[pos];
    char c2 = row1[pos + 1];
    char c3 = row2[pos];
    char c4 = row2[pos + 1];
    
    // Map the codes to Plants enum
    std::map<char, Plants> plant_map = {
        {'G', Plants::grass},
        {'C', Plants::clover},
        {'R', Plants::radishes},
        {'V', Plants::violets}
    };
    
    return {
        plant_map.at(c1),
        plant_map.at(c2),
        plant_map.at(c3),
        plant_map.at(c4)
    };
}

}  // namespace kindergarten_garden
