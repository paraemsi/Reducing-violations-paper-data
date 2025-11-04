#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <array>
#include <cstdint>
#include <stdexcept>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred", 
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    std::int32_t index = -1;
    for (std::int32_t i = 0; i < 12; i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        throw std::invalid_argument("Student not found");
    }
    
    // Split the diagram into two lines
    std::size_t split_pos = diagram.find('\n');
    if (split_pos == std::string::npos) {
        throw std::invalid_argument("Invalid diagram format");
    }
    std::string first_row = diagram.substr(0, split_pos);
    std::string second_row = diagram.substr(split_pos + 1);
    
    // Check if the rows have enough characters
    if (first_row.size() < static_cast<std::size_t>(2 * (index + 1)) || 
        second_row.size() < static_cast<std::size_t>(2 * (index + 1))) {
        throw std::invalid_argument("Diagram doesn't have enough plants");
    }
    
    // Get the plants for the child in the correct order
    std::vector<Plants> result;
    
    // Process first two plants from the first row
    for (std::int32_t i = 0; i < 2; i++) {
        std::size_t pos = static_cast<std::size_t>((2 * index) + i);
        switch (first_row[pos]) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: throw std::invalid_argument("Invalid plant code");
        }
    }
    
    // Process first two plants from the second row
    for (std::int32_t i = 0; i < 2; i++) {
        std::size_t pos = static_cast<std::size_t>((2 * index) + i);
        switch (second_row[pos]) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: throw std::invalid_argument("Invalid plant code");
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
