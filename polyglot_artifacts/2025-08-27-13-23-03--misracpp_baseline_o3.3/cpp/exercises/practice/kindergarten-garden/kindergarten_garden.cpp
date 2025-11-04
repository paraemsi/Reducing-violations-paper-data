#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

const std::vector<std::string> default_students{
    "Alice",  "Bob",     "Charlie", "David",
    "Eve",    "Fred",    "Ginny",   "Harriet",
    "Ileana", "Joseph",  "Kincaid", "Larry"};

Plants garden::char_to_plant(char c) {
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
            throw std::invalid_argument("Invalid plant character");
    }
}

garden::garden(std::string diagram, std::vector<std::string> students) {
    // Remove a possible leading newline
    if (!diagram.empty() && diagram.front() == '\n') {
        diagram.erase(0, 1);
    }

    // Split diagram into two rows
    std::string::size_type pos = diagram.find('\n');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    }

    std::string row1 = diagram.substr(0, pos);
    std::string row2 = diagram.substr(pos + 1);

    // Ensure both rows have equal length and even number of cups
    if (row1.size() != row2.size() || row1.size() % 2 != 0) {
        throw std::invalid_argument("Invalid diagram dimensions");
    }

    // Sort students alphabetically as required
    std::sort(students.begin(), students.end());

    const std::size_t expected_students = row1.size() / 2;
    if (students.size() != expected_students) {
        throw std::invalid_argument("Number of students does not match diagram");
    }

    for (std::size_t i = 0; i < students.size(); ++i) {
        std::vector<Plants> assigned{
            char_to_plant(row1[2 * i]),
            char_to_plant(row1[2 * i + 1]),
            char_to_plant(row2[2 * i]),
            char_to_plant(row2[2 * i + 1])};

        garden_map_.emplace(students[i], std::move(assigned));
    }
}

const std::vector<Plants>& garden::plants(const std::string& student) const {
    auto it = garden_map_.find(student);
    if (it == garden_map_.end()) {
        throw std::out_of_range("Student not found");
    }
    return it->second;
}

std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student,
                             std::vector<std::string> students)
{
    // Ensure the students vector matches the diagram width.
    // Extract first row length to know how many student pairs exist.
    std::string::size_type pos = diagram.find('\n');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    }
    std::size_t expected_students = pos / 2;  // two cups per student

    // Use default list if caller passed an empty vector.
    if (students.empty()) {
        students = default_students;
    }

    // Keep only as many students as the diagram describes.
    if (students.size() < expected_students) {
        throw std::invalid_argument("Not enough students supplied for diagram");
    }
    if (students.size() > expected_students) {
        students.resize(expected_students);
    }

    garden g(diagram, students);
    const auto& vec = g.plants(student);
    return {vec[0], vec[1], vec[2], vec[3]};
}

}  // namespace kindergarten_garden
