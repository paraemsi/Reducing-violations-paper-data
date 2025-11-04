#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    int index = std::distance(children.begin(), it);
    
    // Split the diagram into two rows
    std::istringstream ss(diagram);
    std::string first_row, second_row;
    std::getline(ss, first_row);
    std::getline(ss, second_row);
    
    // Get the plants for the child
    std::vector<Plants> result;
    
    // First row plants
    for (int i = 0; i < 2; i++) {
        char plant_code = first_row[2 * index + i];
        switch (plant_code) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: break;
        }
    }
    
    // Second row plants
    for (int i = 0; i < 2; i++) {
        char plant_code = second_row[2 * index + i];
        switch (plant_code) {
            case 'G': result.push_back(Plants::grass); break;
            case 'C': result.push_back(Plants::clover); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: break;
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
