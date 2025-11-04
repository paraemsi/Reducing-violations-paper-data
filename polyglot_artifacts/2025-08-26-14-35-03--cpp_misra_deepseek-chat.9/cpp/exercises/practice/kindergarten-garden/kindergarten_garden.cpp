#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace kindergarten_garden {

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    if (it == children.end()) {
        // Handle case where student is not found
        // According to the problem, this shouldn't happen
        return {{Plants::grass, Plants::grass, Plants::grass, Plants::grass}};
    }
    std::size_t index = static_cast<std::size_t>(it - children.begin());
    
    // Split the diagram into rows
    std::istringstream iss(diagram);
    std::string row1;
    std::string row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // Ensure the rows are long enough
    if (row1.length() < (index * 2 + 2) || row2.length() < (index * 2 + 2)) {
        // Handle case where rows are not long enough
        return {{Plants::grass, Plants::grass, Plants::grass, Plants::grass}};
    }
    
    // Get plants from both rows
    char plant1 = row1[index * 2];
    char plant2 = row1[(index * 2) + 1];
    char plant3 = row2[index * 2];
    char plant4 = row2[(index * 2) + 1];
    
    // Convert each plant character to the corresponding enum value
    auto to_plant = [](char c) {
        switch (c) {
            case 'G': return Plants::grass;
            case 'C': return Plants::clover;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: 
                // Handle invalid character
                return Plants::grass;
        }
    };
    
    return {{
        to_plant(plant1),
        to_plant(plant2),
        to_plant(plant3),
        to_plant(plant4)
    }};
}

}  // namespace kindergarten_garden
