#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <cstdint>
#include <map>
#include <stdexcept>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& child) {
    // Create a map to get index from child's name
    static const std::map<std::string, std::int32_t> child_index = {
        {"Alice", 0}, {"Bob", 1}, {"Charlie", 2}, {"David", 3},
        {"Eve", 4}, {"Fred", 5}, {"Ginny", 6}, {"Harriet", 7},
        {"Ileana", 8}, {"Joseph", 9}, {"Kincaid", 10}, {"Larry", 11}
    };
    
    // Get the index
    auto it = child_index.find(child);
    if (it == child_index.end()) {
        throw std::invalid_argument("Child not found");
    }
    std::int32_t index = it->second;
    
    // Split the diagram into two lines
    std::size_t split_pos = diagram.find('\n');
    if (split_pos == std::string::npos) {
        throw std::invalid_argument("Invalid diagram format");
    }
    std::string row1 = diagram.substr(0, split_pos);
    std::string row2 = diagram.substr(split_pos + 1);
    
    // Check if the rows are long enough
    std::int32_t start = 2 * index;
    if ((start + 1) >= static_cast<std::int32_t>(row1.length()) || 
        (start + 1) >= static_cast<std::int32_t>(row2.length())) {
        throw std::invalid_argument("Diagram is too short");
    }
    
    // Prepare result
    std::vector<Plants> result;
    result.reserve(4);
    
    // Helper lambda to convert character to Plants enum
    auto convertToPlant = [](char c) -> Plants {
        switch (c) {
            case 'C': return Plants::clover;
            case 'G': return Plants::grass;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: throw std::invalid_argument("Invalid plant code");
        }
    };
    
    // Add plants from first row
    result.push_back(convertToPlant(row1[start]));
    result.push_back(convertToPlant(row1[start + 1]));
    // Add plants from second row
    result.push_back(convertToPlant(row2[start]));
    result.push_back(convertToPlant(row2[start + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
