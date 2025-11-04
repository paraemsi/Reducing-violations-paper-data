#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <stdexcept>

namespace kindergarten_garden {

const std::array<std::string, 12U> garden::default_students{
    "Alice",  "Bob",   "Charlie", "David",  "Eve",     "Fred",
    "Ginny",  "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

Plants garden::char_to_plant(char code)
{
    if (code == 'G') {
        return Plants::grass;
    } else if (code == 'C') {
        return Plants::clover;
    } else if (code == 'R') {
        return Plants::radishes;
    } else if (code == 'V') {
        return Plants::violets;
    } else {
        throw std::invalid_argument("Invalid plant code");
    }
}

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
{
    std::vector<std::string> rows;
    std::string current_row;

    for (char ch : diagram) {
        if (ch == '\n') {
            rows.push_back(current_row);
            current_row.clear();
        } else {
            current_row.push_back(ch);
        }
    }

    if (!current_row.empty()) {
        rows.push_back(current_row);
    }

    if (rows.size() != 2U) {
        throw std::invalid_argument("Diagram must consist of two rows");
    }

    std::vector<std::string> student_list = students;
    if (student_list.empty()) {
        student_list.assign(default_students.begin(), default_students.end());
    }

    /* Ensure cups are assigned according to alphabetical order, as required
       by the specification. */
    std::sort(student_list.begin(), student_list.end());

    const std::size_t expected_length = student_list.size() * 2U;
    if ((rows[0].size() != expected_length) || (rows[1].size() != expected_length)) {
        throw std::invalid_argument("Row length does not match number of students");
    }

    for (std::size_t idx = 0U; idx < student_list.size(); ++idx) {
        std::vector<Plants> assigned;
        assigned.reserve(4U);

        const std::size_t cup_index = idx * 2U;
        assigned.push_back(char_to_plant(rows[0][cup_index]));
        assigned.push_back(char_to_plant(rows[0][cup_index + 1U]));
        assigned.push_back(char_to_plant(rows[1][cup_index]));
        assigned.push_back(char_to_plant(rows[1][cup_index + 1U]));

        m_student_plants.emplace(student_list[idx], assigned);
    }
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    const auto it = m_student_plants.find(student);
    if (it == m_student_plants.end()) {
        throw std::out_of_range("Student not found");
    }
    return it->second;
}

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student,
                              const std::vector<std::string>& students)
{
    const garden g(diagram, students);
    const std::vector<Plants> vec = g.plants(student);
    std::array<Plants, 4U> result{};
    for (std::size_t idx = 0U; idx < 4U; ++idx) {
        result[idx] = vec[idx];
    }
    return result;
}

}  // namespace kindergarten_garden
