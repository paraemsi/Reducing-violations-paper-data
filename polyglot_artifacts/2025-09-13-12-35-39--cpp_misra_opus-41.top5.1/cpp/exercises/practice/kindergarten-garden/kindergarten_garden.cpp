#include "kindergarten_garden.h"
#include <algorithm>
#include <cstdint>
#include <sstream>
#include <vector>

namespace kindergarten_garden {

namespace {

// Convert plant code character to Plants enum
Plants plant_code_to_enum(char code) {
    switch (code) {
        case 'G':
            return Plants::grass;
        case 'C':
            return Plants::clover;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            return Plants::grass; // Default fallback
    }
}

// Get the index of a student based on alphabetical order
std::int32_t get_student_index(const std::string& student) {
    // List of students in alphabetical order
    const std::vector<std::string> students = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    auto it = std::find(students.begin(), students.end(), student);
    if (it != students.end()) {
        return static_cast<std::int32_t>(it - students.begin());
    }
    return -1;
}

} // anonymous namespace

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    std::array<Plants, 4> result{};
    
    // Get student index
    std::int32_t student_index = get_student_index(student);
    if (student_index == -1) {
        return result; // Student not found, return default array
    }
    
    // Split diagram into two rows
    std::istringstream stream(diagram);
    std::string row1, row2;
    std::getline(stream, row1);
    std::getline(stream, row2);
    
    // Each student gets 2 consecutive cups per row
    // Calculate the starting position for this student's cups
    std::int32_t start_pos = student_index * 2;
    
    // Validate that we have enough cups for this student
    if ((start_pos + 1) >= static_cast<std::int32_t>(row1.length()) ||
        (start_pos + 1) >= static_cast<std::int32_t>(row2.length())) {
        return result; // Not enough cups
    }
    
    // Get the 4 plants for this student (2 from each row)
    result[0] = plant_code_to_enum(row1[static_cast<std::size_t>(start_pos)]);
    result[1] = plant_code_to_enum(row1[static_cast<std::size_t>(start_pos + 1)]);
    result[2] = plant_code_to_enum(row2[static_cast<std::size_t>(start_pos)]);
    result[3] = plant_code_to_enum(row2[static_cast<std::size_t>(start_pos + 1)]);
    
    return result;
}

}  // namespace kindergarten_garden
