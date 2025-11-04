#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& child) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred", 
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the child
    auto it = std::find(children.begin(), children.end(), child);
    // Since child is always valid, index will be within bounds
    std::int32_t index = static_cast<std::int32_t>(it - children.begin());
    
    // Split the diagram into two rows
    std::size_t split_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, split_pos);
    std::string row2 = diagram.substr(split_pos + 1);
    
    // Each child has 2 plants per row, so calculate positions
    std::int32_t start_pos = 2 * index;
    
    // Get the plant codes
    std::vector<Plants> result;
    
    // Process first row
    for (std::int32_t i = start_pos; i < (start_pos + 2); ++i) {
        switch (row1[i]) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: break;
        }
    }
    
    // Process second row
    for (std::int32_t i = start_pos; i < (start_pos + 2); ++i) {
        switch (row2[i]) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: break;
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
