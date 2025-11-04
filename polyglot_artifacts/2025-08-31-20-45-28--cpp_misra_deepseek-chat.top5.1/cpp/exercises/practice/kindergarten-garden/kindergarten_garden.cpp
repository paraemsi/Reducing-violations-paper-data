#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <sstream>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    if (it == children.end()) {
        return {};
    }
    int index = static_cast<int>(it - children.begin());
    
    // Split the diagram into two rows
    std::istringstream iss(diagram);
    std::string first_row;
    std::string second_row;
    std::getline(iss, first_row);
    std::getline(iss, second_row);
    
    // Get the plants for the child in the correct order
    std::vector<Plants> result;
    result.reserve(4); // We always have 4 plants per student
    
    // Process each plant in order
    int start_pos = 2 * index;
    // First row plants
    for (int i = 0; i < 2; i++) {
        char plant_code = first_row[start_pos + i];
        switch (plant_code) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
        }
    }
    // Second row plants
    for (int i = 0; i < 2; i++) {
        char plant_code = second_row[start_pos + i];
        switch (plant_code) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
