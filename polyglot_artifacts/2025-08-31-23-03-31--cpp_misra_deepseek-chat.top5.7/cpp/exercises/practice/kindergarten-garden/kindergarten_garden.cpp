#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <array>
#include <cstdint>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    std::int32_t index = 0;
    for (std::int32_t i = 0; i < 12; i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into two rows by finding the newline
    std::size_t split_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, split_pos);
    std::string row2 = diagram.substr(split_pos + 1);
    
    // Get the plants for the child
    std::vector<Plants> result;
    
    // Calculate positions
    const std::int32_t start_pos = index * 2;
    
    // Get plant codes from both rows
    const char plant_code1 = row1[start_pos];
    const char plant_code2 = row1[start_pos + 1];
    const char plant_code3 = row2[start_pos];
    const char plant_code4 = row2[start_pos + 1];
    
    // Helper lambda to convert plant code to enum
    auto convert_plant = [](const char code) -> Plants {
        if (code == 'G') {
            return Plants::grass;
        } 
        else { 
            if (code == 'C') {
                return Plants::clover;
            } 
            else { 
                if (code == 'R') {
                    return Plants::radishes;
                } 
                else { 
                    if (code == 'V') {
                        return Plants::violets;
                    }
                }
            }
        }
        // Default case, though according to the problem, this should never happen
        return Plants::grass;
    };
    
    result.push_back(convert_plant(plant_code1));
    result.push_back(convert_plant(plant_code2));
    result.push_back(convert_plant(plant_code3));
    result.push_back(convert_plant(plant_code4));
    
    return result;
}

}  // namespace kindergarten_garden
