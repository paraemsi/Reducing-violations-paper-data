#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& child, const std::string& diagram) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David", 
        "Eve", "Fred", "Ginny", "Harriet", 
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the child
    auto it = std::find(children.begin(), children.end(), child);
    if (it == children.end()) {
        return {};
    }
    int index = std::distance(children.begin(), it);
    
    // Split the diagram into lines
    std::istringstream iss(diagram);
    std::string row1, row2;
    std::getline(iss, row1);
    std::getline(iss, row2);
    
    // Get the plants for the child
    std::vector<Plants> result;
    int start_pos = 2 * index;
    
    // Process first row
    for (int i = 0; i < 2; i++) {
        char c = row1[start_pos + i];
        switch (c) {
            case 'C': result.push_back(Plants::clover); break;
            case 'G': result.push_back(Plants::grass); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: break;
        }
    }
    
    // Process second row
    for (int i = 0; i < 2; i++) {
        char c = row2[start_pos + i];
        switch (c) {
            case 'C': result.push_back(Plants::clover); break;
            case 'G': result.push_back(Plants::grass); break;
            case 'R': result.push_back(Plants::radishes); break;
            case 'V': result.push_back(Plants::violets); break;
            default: break;
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
