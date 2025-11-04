#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <cstdint>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    std::int32_t index = static_cast<std::int32_t>(it - children.begin());
    
    // Split the diagram into rows
    std::size_t newline_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);
    
    // Get the plants for the child
    std::vector<Plants> result;
    
    // Calculate indices
    std::int32_t pos1 = 2 * index;
    std::int32_t pos2 = 2 * index + 1;
    
    // Process first row
    if (row1.length() > static_cast<std::size_t>(pos1)) {
        switch (row1[pos1]) {
            case 'G': result.emplace_back(Plants::grass); break;
            case 'C': result.emplace_back(Plants::clover); break;
            case 'R': result.emplace_back(Plants::radishes); break;
            case 'V': result.emplace_back(Plants::violets); break;
            default: break;
        }
    }
    if (row1.length() > static_cast<std::size_t>(pos2)) {
        switch (row1[pos2]) {
            case 'G': result.emplace_back(Plants::grass); break;
            case 'C': result.emplace_back(Plants::clover); break;
            case 'R': result.emplace_back(Plants::radishes); break;
            case 'V': result.emplace_back(Plants::violets); break;
            default: break;
        }
    }
    
    // Process second row
    if (row2.length() > static_cast<std::size_t>(pos1)) {
        switch (row2[pos1]) {
            case 'G': result.emplace_back(Plants::grass); break;
            case 'C': result.emplace_back(Plants::clover); break;
            case 'R': result.emplace_back(Plants::radishes); break;
            case 'V': result.emplace_back(Plants::violets); break;
            default: break;
        }
    }
    if (row2.length() > static_cast<std::size_t>(pos2)) {
        switch (row2[pos2]) {
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
