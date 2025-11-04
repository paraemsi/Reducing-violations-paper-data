#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cstdint>
#include <array>

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
    // Use std::size_t which is appropriate for indexing, but cast to uint32_t to follow rules
    std::uint32_t index = static_cast<std::uint32_t>(it - children.begin());
    
    // Split the diagram into two rows
    std::istringstream iss(diagram);
    std::string row1;
    std::string row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // Each child has 2 plants per row, so their index starts at 2*index
    std::uint32_t start_pos = static_cast<std::uint32_t>(2U) * index;
    
    // Get the plants from both rows
    std::string plants_chars;
    plants_chars += row1.substr(static_cast<std::size_t>(start_pos), 2U);
    plants_chars += row2.substr(static_cast<std::size_t>(start_pos), 2U);
    
    // Map each character to the corresponding plant enum
    std::map<char, Plants> plant_map = {
        {'G', Plants::grass},
        {'C', Plants::clover},
        {'R', Plants::radishes},
        {'V', Plants::violets}
    };
    
    // Convert to plant enums
    std::vector<Plants> result;
    for (char c : plants_chars) {
        result.push_back(plant_map.at(c));
    }
    
    return result;
}

}  // namespace kindergarten_garden
