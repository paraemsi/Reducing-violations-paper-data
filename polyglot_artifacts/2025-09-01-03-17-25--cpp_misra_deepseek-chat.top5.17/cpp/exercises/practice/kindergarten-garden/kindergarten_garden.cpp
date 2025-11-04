#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the child
    auto it = std::find(children.begin(), children.end(), student);
    std::int32_t index = static_cast<std::int32_t>(it - children.begin());
    
    // Split the diagram into two rows
    std::size_t newline_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr((newline_pos + 1));
    
    // Each child has two plants per row, at positions 2*index and 2*index +1
    std::vector<Plants> result;
    
    // Get plants from first row
    // Using character comparisons which are allowed
    char plant1 = row1[(2 * index)];
    char plant2 = row1[((2 * index) + 1)];
    
    // Get plants from second row
    char plant3 = row2[(2 * index)];
    char plant4 = row2[((2 * index) + 1)];
    
    // Convert each character to the corresponding enum
    auto convert_plant = [](char c) -> Plants {
        if (c == 'G') {
            return Plants::grass;
        } else {
            if (c == 'C') {
                return Plants::clover;
            } else {
                if (c == 'R') {
                    return Plants::radishes;
                } else {
                    if (c == 'V') {
                        return Plants::violets;
                    }
                }
            }
        }
        // Handle error case - though according to the problem, all inputs are valid
        return Plants::grass;
    };
    
    result.push_back(convert_plant(plant1));
    result.push_back(convert_plant(plant2));
    result.push_back(convert_plant(plant3));
    result.push_back(convert_plant(plant4));
    
    return result;
}

}  // namespace kindergarten_garden
