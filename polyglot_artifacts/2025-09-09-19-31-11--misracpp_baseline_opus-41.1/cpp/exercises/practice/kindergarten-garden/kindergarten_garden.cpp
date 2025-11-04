#include "kindergarten_garden.h"
#include <algorithm>
#include <vector>

namespace kindergarten_garden {

Plants charToPlant(char c) {
    switch (c) {
        case 'G':
            return Plants::grass;
        case 'C':
            return Plants::clover;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            return Plants::grass;  // Default case, shouldn't happen with valid input
    }
}

int getStudentIndex(const std::string& student) {
    // Students in alphabetical order
    std::vector<std::string> students = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    auto it = std::find(students.begin(), students.end(), student);
    if (it != students.end()) {
        return std::distance(students.begin(), it);
    }
    
    return 0;  // Default to first position if student not found
}

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    size_t newline_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, newline_pos);
    std::string row2 = diagram.substr(newline_pos + 1);
    
    int index = getStudentIndex(student);
    int position = index * 2;  // Each student gets 2 cups per row
    
    std::vector<Plants> result;
    
    // Add the two plants from row 1
    result.push_back(charToPlant(row1[position]));
    result.push_back(charToPlant(row1[position + 1]));
    
    // Add the two plants from row 2
    result.push_back(charToPlant(row2[position]));
    result.push_back(charToPlant(row2[position + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
