#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    int index = it - children.begin();
    
    // Split the diagram into two rows
    // Find the newline position to split the string
    size_t newline_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);
    
    // Get the plants for the child
    std::vector<Plants> result;
    
    // Add both plants from the first row
    int start_pos = 2 * index;
    for (int i = 0; i < 2; i++) {
        char plant_code = row1[start_pos + i];
        switch (plant_code) {
            case 'G': result.emplace_back(Plants::grass); break;
            case 'C': result.emplace_back(Plants::clover); break;
            case 'R': result.emplace_back(Plants::radishes); break;
            case 'V': result.emplace_back(Plants::violets); break;
            default: break;
        }
    }
    
    // Add both plants from the second row
    for (int i = 0; i < 2; i++) {
        char plant_code = row2[start_pos + i];
        switch (plant_code) {
            case 'G': result.emplace_back(Plants::grass); break;
            case 'C': result.emplace_back(Plants::clover); break;
            case 'R': result.emplace_back(Plants::radishes); break;
            case 'V': result.emplace_back(Plants::violets); break;
            default: break;
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
