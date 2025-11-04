#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <map>
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
    std::size_t index = 0;
    for (std::size_t i = 0; i < children.size(); ++i) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into two rows by finding the newline
    std::size_t split_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, split_pos);
    std::string row2 = diagram.substr(split_pos + 1);
    
    // Get the plant codes for the child
    std::size_t start_pos = 2 * index;
    std::vector<Plants> result;
    
    // Map plant codes to enum values
    std::map<char, Plants> plant_map = {
        {'G', Plants::grass},
        {'C', Plants::clover},
        {'R', Plants::radishes},
        {'V', Plants::violets}
    };
    
    // Add each plant in order
    result.push_back(plant_map[row1[start_pos]]);
    result.push_back(plant_map[row1[start_pos + 1]]);
    result.push_back(plant_map[row2[start_pos]]);
    result.push_back(plant_map[row2[start_pos + 1]]);
    
    return result;
}

}  // namespace kindergarten_garden
