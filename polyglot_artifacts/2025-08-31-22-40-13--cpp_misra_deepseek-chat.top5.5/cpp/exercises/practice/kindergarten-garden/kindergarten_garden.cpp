#include "kindergarten_garden.h"
#include <string>
#include <vector>
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
    std::int32_t index = 0;
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
    
    // Process first row
    for (std::int32_t i = 0; i < 2; i++) {
        const char plant_code = row1[index * 2 + i];
        if (plant_code == 'G') {
            result.push_back(Plants::grass);
        } else if (plant_code == 'C') {
            result.push_back(Plants::clover);
        } else if (plant_code == 'R') {
            result.push_back(Plants::radishes);
        } else if (plant_code == 'V') {
            result.push_back(Plants::violets);
        }
    }
    
    // Process second row
    for (std::int32_t i = 0; i < 2; i++) {
        const char plant_code = row2[index * 2 + i];
        if (plant_code == 'G') {
            result.push_back(Plants::grass);
        } else if (plant_code == 'C') {
            result.push_back(Plants::clover);
        } else if (plant_code == 'R') {
            result.push_back(Plants::radishes);
        } else if (plant_code == 'V') {
            result.push_back(Plants::violets);
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
