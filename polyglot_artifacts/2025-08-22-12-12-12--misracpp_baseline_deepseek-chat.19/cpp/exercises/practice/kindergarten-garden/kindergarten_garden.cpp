#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
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
    int index = std::distance(children.begin(), 
                              std::find(children.begin(), children.end(), student));
    
    // Split the diagram into rows by newline
    size_t newline_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);
    
    // Calculate the starting position for the child's plants
    int start_pos = index * 2;
    
    // Prepare the result
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
    
    // Add plants from first row
    result.push_back(charToPlant(row1[start_pos]));
    result.push_back(charToPlant(row1[start_pos + 1]));
    
    // Add plants from second row
    result.push_back(charToPlant(row2[start_pos]));
    result.push_back(charToPlant(row2[start_pos + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
