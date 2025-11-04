#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <cstdint>

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
    
    // Split the diagram into two rows
    std::istringstream iss(diagram);
    std::string row1;
    std::string row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // Get the plants for the child
    std::vector<Plants> result;
    std::int32_t start_pos = index * 2;
    
    // Process each plant in both rows
    for (std::int32_t i = start_pos; i < (start_pos + 2); i++) {
        const char plant_char = row1[i];
        if (plant_char == 'G') {
            result.emplace_back(Plants::grass);
        } else { 
            if (plant_char == 'C') {
                result.emplace_back(Plants::clover);
            } else { 
                if (plant_char == 'R') {
                    result.emplace_back(Plants::radishes);
                } else { 
                    if (plant_char == 'V') {
                        result.emplace_back(Plants::violets);
                    }
                }
            }
        }
    }
    for (std::int32_t i = start_pos; i < (start_pos + 2); i++) {
        const char plant_char = row2[i];
        if (plant_char == 'G') {
            result.emplace_back(Plants::grass);
        } else { 
            if (plant_char == 'C') {
                result.emplace_back(Plants::clover);
            } else { 
                if (plant_char == 'R') {
                    result.emplace_back(Plants::radishes);
                } else { 
                    if (plant_char == 'V') {
                        result.emplace_back(Plants::violets);
                    }
                }
            }
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
