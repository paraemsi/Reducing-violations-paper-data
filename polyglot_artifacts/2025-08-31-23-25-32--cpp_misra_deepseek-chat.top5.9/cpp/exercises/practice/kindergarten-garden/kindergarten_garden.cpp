#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <sstream>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    std::size_t index = static_cast<std::size_t>(it - children.begin());
    
    // Split the diagram into two rows by finding the newline
    std::size_t split_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, split_pos);
    std::string row2 = diagram.substr(split_pos + 1);
    
    // Calculate the starting position for the child's plants
    std::size_t start_pos = 2 * index;
    
    // Get the plants
    std::vector<Plants> result;
    
    // Helper function to convert character to plant enum
    auto convert = [](char c) -> Plants {
        switch (c) {
            case 'C': return Plants::clover;
            case 'G': return Plants::grass;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::clover; // Should not happen according to the problem
        }
    };
    
    // Add plants from the first row
    result.push_back(convert(row1[start_pos]));
    result.push_back(convert(row1[start_pos + 1]));
    // Add plants from the second row
    result.push_back(convert(row2[start_pos]));
    result.push_back(convert(row2[start_pos + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
