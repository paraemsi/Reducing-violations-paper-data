#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <cstdint>

namespace kindergarten_garden {

// Define an alias for index type
using index_t = std::int32_t;

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred", 
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    index_t index = -1;
    for (index_t i = 0; i < 12; i++) {
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
    
    // Process first row - both cups
    for (index_t i = 0; i < 2; i++) {
        const char plant_char = row1[(2 * index) + i];
        switch (plant_char) {
            case 'G': result.emplace_back(Plants::grass); break;
            case 'C': result.emplace_back(Plants::clover); break;
            case 'R': result.emplace_back(Plants::radishes); break;
            case 'V': result.emplace_back(Plants::violets); break;
        }
    }
    
    // Process second row - both cups
    for (index_t i = 0; i < 2; i++) {
        const char plant_char = row2[(2 * index) + i];
        switch (plant_char) {
            case 'G': result.emplace_back(Plants::grass); break;
            case 'C': result.emplace_back(Plants::clover); break;
            case 'R': result.emplace_back(Plants::radishes); break;
            case 'V': result.emplace_back(Plants::violets); break;
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
