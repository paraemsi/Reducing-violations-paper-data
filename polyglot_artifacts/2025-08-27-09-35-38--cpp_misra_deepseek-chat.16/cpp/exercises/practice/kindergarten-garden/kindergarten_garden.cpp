#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <array>
#include <sstream>
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
    std::ptrdiff_t index_diff = it - children.begin();
    std::uint32_t index = static_cast<std::uint32_t>(index_diff);
    
    // Split the diagram into rows
    std::vector<std::string> rows;
    std::istringstream iss(diagram);
    std::string line;
    while (std::getline(iss, line)) {
        rows.push_back(line);
    }
    
    // Ensure we have exactly two rows
    if (rows.size() < 2) {
        // Handle error case, though according to instructions there should always be two rows
        return {};
    }
    
    const std::string& row1 = rows[0];
    const std::string& row2 = rows[1];
    
    // Get the plants for the child
    std::vector<Plants> result;
    
    // For each plant code, map to enum
    // First two plants from the first row
    for (std::uint32_t i = 0; i < 2; i++) {
        std::uint32_t pos = (2U * index) + i;
        char c = row1[pos];
        switch (c) {
            case 'C': result.emplace_back(Plants::clover); break;
            case 'G': result.emplace_back(Plants::grass); break;
            case 'R': result.emplace_back(Plants::radishes); break;
            case 'V': result.emplace_back(Plants::violets); break;
            default: break;
        }
    }
    
    // Then two plants from the second row
    for (std::uint32_t i = 0; i < 2; i++) {
        std::uint32_t pos = (2U * index) + i;
        char c = row2[pos];
        switch (c) {
            case 'C': result.emplace_back(Plants::clover); break;
            case 'G': result.emplace_back(Plants::grass); break;
            case 'R': result.emplace_back(Plants::radishes); break;
            case 'V': result.emplace_back(Plants::violets); break;
            default: break;
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
