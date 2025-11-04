#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // Fixed list of children
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    std::size_t index = static_cast<std::size_t>(it - children.begin());
    
    // Split the diagram into rows
    std::size_t newline_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);
    
    // Calculate positions for the child's plants
    std::size_t pos = 2 * index;
    
    // Get the plants
    std::vector<Plants> result;
    
    // Helper function to convert character to plant enum
    auto convert = [](char c) -> Plants {
        switch (c) {
            case 'G': return Plants::grass;
            case 'C': return Plants::clover;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::grass; // Should not happen according to the problem
        }
    };
    
    result.push_back(convert(row1[pos]));
    result.push_back(convert(row1[pos + 1]));
    result.push_back(convert(row2[pos]));
    result.push_back(convert(row2[pos + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
