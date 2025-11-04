#include "kindergarten_garden.h"
#include <vector>
#include <string>
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
    // The diagram may be a single string with a newline separating the two rows
    std::istringstream iss(diagram);
    std::string line;
    std::vector<std::string> rows;
    
    while (std::getline(iss, line)) {
        if (!line.empty()) {
            rows.push_back(line);
        }
    }
    
    // We should have exactly two rows
    // Get the plants for the child
    std::vector<Plants> result;
    
    // Calculate start index
    const std::size_t start_pos = 2 * index;
    
    // Process first row
    for (std::size_t i = start_pos; i < (start_pos + 2); i++) {
        switch (rows[0][i]) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: break;
        }
    }
    
    // Process second row
    for (std::size_t i = start_pos; i < (start_pos + 2); i++) {
        switch (rows[1][i]) {
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
