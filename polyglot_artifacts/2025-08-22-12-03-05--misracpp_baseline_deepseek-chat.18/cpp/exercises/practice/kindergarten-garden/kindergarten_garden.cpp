#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // Fixed list of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David", 
        "Eve", "Fred", "Ginny", "Harriet", 
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    int index = it - children.begin();
    
    // Split the diagram into lines
    std::istringstream iss(diagram);
    std::string line;
    std::vector<std::string> rows;
    while (std::getline(iss, line)) {
        if (!line.empty()) {
            rows.push_back(line);
        }
    }
    
    // Make sure we have exactly two rows
    if (rows.size() != 2) {
        // Handle error case
        return {};
    }
    
    const std::string& row1 = rows[0];
    const std::string& row2 = rows[1];
    
    // Map plant codes to enum values
    std::map<char, Plants> plant_map = {
        {'G', Plants::grass},
        {'C', Plants::clover},
        {'R', Plants::radishes},
        {'V', Plants::violets}
    };
    
    // Get the plants for the child
    std::vector<Plants> result;
    int start_pos = 2 * index;
    result.push_back(plant_map[row1[start_pos]]);
    result.push_back(plant_map[row1[start_pos + 1]]);
    result.push_back(plant_map[row2[start_pos]]);
    result.push_back(plant_map[row2[start_pos + 1]]);
    
    return result;
}

}  // namespace kindergarten_garden
