#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cstdint>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    std::int32_t index = 0;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(children.size()); i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into lines
    std::vector<std::string> rows;
    std::istringstream iss(diagram);
    std::string line;
    while (std::getline(iss, line, '\n')) {
        if (!line.empty()) {
            rows.push_back(line);
        }
    }
    
    // We should have exactly two rows
    if (rows.size() != 2) {
        return {};
    }
    
    const std::string& row1 = rows[0];
    const std::string& row2 = rows[1];
    
    // Get the plants for the child
    std::vector<Plants> result;
    
    // Calculate positions
    std::int32_t pos = 2 * index;
    
    // First row plants
    char plant1 = row1[pos];
    char plant2 = row1[pos + 1];
    
    // Second row plants
    char plant3 = row2[pos];
    char plant4 = row2[pos + 1];
    
    // Map each plant code to enum
    if (plant1 == 'G') { result.push_back(Plants::grass); }
    else if (plant1 == 'C') { result.push_back(Plants::clover); }
    else if (plant1 == 'R') { result.push_back(Plants::radishes); }
    else if (plant1 == 'V') { result.push_back(Plants::violets); }
    
    if (plant2 == 'G') { result.push_back(Plants::grass); }
    else if (plant2 == 'C') { result.push_back(Plants::clover); }
    else if (plant2 == 'R') { result.push_back(Plants::radishes); }
    else if (plant2 == 'V') { result.push_back(Plants::violets); }
    
    if (plant3 == 'G') { result.push_back(Plants::grass); }
    else if (plant3 == 'C') { result.push_back(Plants::clover); }
    else if (plant3 == 'R') { result.push_back(Plants::radishes); }
    else if (plant3 == 'V') { result.push_back(Plants::violets); }
    
    if (plant4 == 'G') { result.push_back(Plants::grass); }
    else if (plant4 == 'C') { result.push_back(Plants::clover); }
    else if (plant4 == 'R') { result.push_back(Plants::radishes); }
    else if (plant4 == 'V') { result.push_back(Plants::violets); }
    
    return result;
}

}  // namespace kindergarten_garden
