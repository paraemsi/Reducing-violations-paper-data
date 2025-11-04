#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <cstddef>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred", 
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    std::size_t index = 0;
    for (std::size_t i = 0; i < children.size(); i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into two rows
    std::istringstream iss(diagram);
    std::string row1;
    std::string row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // Each child has 2 plants per row, so their plants are at index*2 to index*2+1
    std::vector<Plants> result;
    
    // Process first row
    for (std::size_t i = index * 2; i <= (index * 2 + 1); i++) {
        switch (row1[i]) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: break;
        }
    }
    
    // Process second row
    for (std::size_t i = index * 2; i <= (index * 2 + 1); i++) {
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
