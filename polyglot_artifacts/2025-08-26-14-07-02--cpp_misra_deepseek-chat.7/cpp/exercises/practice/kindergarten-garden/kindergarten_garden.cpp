#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <array>

namespace kindergarten_garden {

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred", 
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    int index = static_cast<int>(it - children.begin());
    
    // Split the diagram into exactly two lines
    std::istringstream iss(diagram);
    std::string first_row;
    std::string second_row;
    std::getline(iss, first_row);
    std::getline(iss, second_row);
    
    // Prepare the result array
    std::array<Plants, 4> result;
    
    // Process first row
    int start_pos = index * 2;
    for (int i = 0; i < 2; ++i) {
        char c = first_row[start_pos + i];
        switch (c) {
            case 'G': result[i] = Plants::grass; break;
            case 'C': result[i] = Plants::clover; break;
            case 'R': result[i] = Plants::radishes; break;
            case 'V': result[i] = Plants::violets; break;
            default: break;
        }
    }
    
    // Process second row
    for (int i = 0; i < 2; ++i) {
        char c = second_row[start_pos + i];
        switch (c) {
            case 'G': result[2 + i] = Plants::grass; break;
            case 'C': result[2 + i] = Plants::clover; break;
            case 'R': result[2 + i] = Plants::radishes; break;
            case 'V': result[2 + i] = Plants::violets; break;
            default: break;
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
