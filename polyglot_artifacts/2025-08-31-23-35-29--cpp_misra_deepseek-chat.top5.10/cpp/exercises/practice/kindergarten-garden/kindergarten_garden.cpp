#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    if (it == children.end()) {
        throw std::invalid_argument("Student not found");
    }
    int index = static_cast<int>(it - children.begin());
    
    // Split the diagram into two rows
    size_t split_pos = diagram.find('\n');
    if (split_pos == std::string::npos) {
        throw std::invalid_argument("Invalid diagram format");
    }
    std::string row1 = diagram.substr(0, split_pos);
    std::string row2 = diagram.substr(split_pos + 1);
    
    // Check if the rows are long enough
    if (row1.length() < (2 * index + 2) || row2.length() < (2 * index + 2)) {
        throw std::invalid_argument("Diagram too short");
    }
    
    // Get the plants in the correct order
    std::vector<Plants> result;
    result.reserve(4);
    
    // Process each plant in order
    for (int i = 0; i < 2; i++) {
        char c1 = row1[2 * index + i];
        switch (c1) {
            case 'C': result.push_back(Plants::clover); break;
            case 'G': result.push_back(Plants::grass); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: throw std::invalid_argument("Invalid plant code");
        }
    }
    
    for (int i = 0; i < 2; i++) {
        char c2 = row2[2 * index + i];
        switch (c2) {
            case 'C': result.push_back(Plants::clover); break;
            case 'G': result.push_back(Plants::grass); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: throw std::invalid_argument("Invalid plant code");
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
