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
    std::int32_t index = static_cast<std::int32_t>(std::distance(children.begin(), it));
    
    // Split the diagram into two rows
    std::istringstream iss(diagram);
    std::string row1;
    std::string row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // Each child has 2 plants per row, so their plants are at index*2 to index*2+1
    std::vector<Plants> result;
    
    // Process first row
    for (std::int32_t i = (index * 2); i <= ((index * 2) + 1); i++) {
        char c = row1[static_cast<std::size_t>(i)];
        if (c == 'G') {
            result.push_back(Plants::grass);
        } else {
            if (c == 'C') {
                result.push_back(Plants::clover);
            } else {
                if (c == 'R') {
                    result.push_back(Plants::radishes);
                } else {
                    if (c == 'V') {
                        result.push_back(Plants::violets);
                    }
                }
            }
        }
    }
    
    // Process second row
    for (std::int32_t i = (index * 2); i <= ((index * 2) + 1); i++) {
        char c = row2[static_cast<std::size_t>(i)];
        if (c == 'G') {
            result.push_back(Plants::grass);
        } else {
            if (c == 'C') {
                result.push_back(Plants::clover);
            } else {
                if (c == 'R') {
                    result.push_back(Plants::radishes);
                } else {
                    if (c == 'V') {
                        result.push_back(Plants::violets);
                    }
                }
            }
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
