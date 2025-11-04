#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>
#include <cstdint>

namespace kindergarten_garden {

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    const std::int32_t index = static_cast<std::int32_t>(it - children.begin());
    
    // Split the diagram into two rows
    std::istringstream iss(diagram);
    std::string row1;
    std::string row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // Get the plants for the child
    std::array<Plants, 4> result;
    std::size_t result_index = 0;
    
    // Calculate start and end indices
    const std::int32_t start_index = 2 * index;
    const std::int32_t end_index = 2 * index + 1;
    
    // Process first row
    for (std::int32_t i = start_index; i <= end_index; i++) {
        const char plant_char = row1[static_cast<std::size_t>(i)];
        if (plant_char == 'G') {
            result[result_index] = Plants::grass;
        } else if (plant_char == 'C') {
            result[result_index] = Plants::clover;
        } else if (plant_char == 'R') {
            result[result_index] = Plants::radishes;
        } else if (plant_char == 'V') {
            result[result_index] = Plants::violets;
        }
        result_index++;
    }
    
    // Process second row
    for (std::int32_t i = start_index; i <= end_index; i++) {
        const char plant_char = row2[static_cast<std::size_t>(i)];
        if (plant_char == 'G') {
            result[result_index] = Plants::grass;
        } else if (plant_char == 'C') {
            result[result_index] = Plants::clover;
        } else if (plant_char == 'R') {
            result[result_index] = Plants::radishes;
        } else if (plant_char == 'V') {
            result[result_index] = Plants::violets;
        }
        result_index++;
    }
    
    return result;
}

}  // namespace kindergarten_garden
