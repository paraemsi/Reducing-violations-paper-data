#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
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
    
    // Split the diagram into rows
    // Find the newline position to split the string
    size_t newline_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);
    
    // Each child gets 2 plants per row, at positions 2*index and 2*index +1
    std::vector<Plants> result;
    
    // Helper function to convert char to Plants
    auto charToPlant = [](char c) -> Plants {
        switch (c) {
            case 'C': return Plants::clover;
            case 'G': return Plants::grass;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::clover; // Should not happen according to the problem
        }
    };
    
    // Add plants from the first row
    result.push_back(charToPlant(row1[2 * index]));
    result.push_back(charToPlant(row1[2 * index + 1]));
    
    // Add plants from the second row
    result.push_back(charToPlant(row2[2 * index]));
    result.push_back(charToPlant(row2[2 * index + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
