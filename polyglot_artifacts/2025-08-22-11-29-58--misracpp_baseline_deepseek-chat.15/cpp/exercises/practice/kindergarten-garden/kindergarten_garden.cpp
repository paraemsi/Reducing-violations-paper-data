#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    int index = std::distance(children.begin(), it);
    
    // Split the diagram into two rows
    std::istringstream ss(diagram);
    std::string row1, row2;
    std::getline(ss, row1);
    std::getline(ss, row2);
    
    // Plant code to enum mapping
    std::map<char, Plants> plant_map = {
        {'G', Plants::grass},
        {'C', Plants::clover},
        {'R', Plants::radishes},
        {'V', Plants::violets}
    };
    
    // Get the plants for the child
    std::vector<Plants> result;
    // First row: two plants at index*2
    result.push_back(plant_map[row1[index * 2]]);
    result.push_back(plant_map[row1[index * 2 + 1]]);
    // Second row: two plants at index*2
    result.push_back(plant_map[row2[index * 2]]);
    result.push_back(plant_map[row2[index * 2 + 1]]);
    
    return result;
}

}  // namespace kindergarten_garden
