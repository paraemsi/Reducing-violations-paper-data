#include "kindergarten_garden.h"

#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <array>

namespace kindergarten_garden {

namespace {

/* Default list of students in alphabetical order */
const std::array<std::string, 12U> default_students = {
    "Alice",  "Bob",   "Charlie", "David",
    "Eve",    "Fred",  "Ginny",   "Harriet",
    "Ileana", "Joseph","Kincaid", "Larry"
};

}  // unnamed namespace

/* Translate the diagram character into a Plant enum value */
Plant Garden::char_to_plant(char code)
{
    if (code == 'G') {
        return Plant::grass;
    } else if (code == 'C') {
        return Plant::clover;
    } else if (code == 'R') {
        return Plant::radishes;
    } else if (code == 'V') {
        return Plant::violets;
    } else {
        throw std::invalid_argument("Invalid plant code");
    }
}

/* Populate the mapping from student → four plants */
void Garden::assign_plants(const std::string& row1,
                           const std::string& row2,
                           const std::vector<std::string>& students,
                           std::unordered_map<std::string, std::vector<Plant>>& out_map)
{
    const std::size_t cups_per_student = 2U;
    const std::size_t expected_length =
        static_cast<std::size_t>(students.size()) * cups_per_student;

    if ((row1.length() != row2.length()) ||
        (row1.length() != expected_length)) {
        throw std::invalid_argument("Diagram rows have unexpected length");
    }

    for (std::size_t i = 0U; i < students.size(); ++i) {
        const std::size_t start_index = static_cast<std::size_t>(2U * i);

        const Plant p1 = char_to_plant(row1.at(start_index));
        const Plant p2 = char_to_plant(row1.at(start_index + 1U));
        const Plant p3 = char_to_plant(row2.at(start_index));
        const Plant p4 = char_to_plant(row2.at(start_index + 1U));

        out_map[students.at(i)] = {p1, p2, p3, p4};
    }
}

/* Constructor using the default student list */
Garden::Garden(const std::string& diagram)
{
    std::istringstream stream(diagram);
    std::string row1;
    std::string row2;

    /* The first getline may read an empty line if the diagram starts with '\n' */
    (void)std::getline(stream, row1);
    (void)std::getline(stream, row2);
    if (row1.empty()) {
        row1 = row2;
        (void)std::getline(stream, row2);
    }

    const std::size_t num_students = static_cast<std::size_t>(row1.length() / 2U);

    const std::vector<std::string> students(
        default_students.begin(),
        default_students.begin() + static_cast<std::ptrdiff_t>(num_students));

    assign_plants(row1, row2, students, student_plants_);
}

/* Constructor with caller-supplied student order */
Garden::Garden(const std::string& diagram, const std::vector<std::string>& students)
{
    std::istringstream stream(diagram);
    std::string row1;
    std::string row2;

    (void)std::getline(stream, row1);
    (void)std::getline(stream, row2);
    if (row1.empty()) {
        row1 = row2;
        (void)std::getline(stream, row2);
    }

    assign_plants(row1, row2, students, student_plants_);
}

/* Retrieve the four plants belonging to the named student */
std::vector<Plant> Garden::plants(const std::string& student) const
{
    const auto it = student_plants_.find(student);
    if (it == student_plants_.end()) {
        return {};
    } else {
        return it->second;
    }
}

/* Free helper wrapper required by the test suite */
std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student)
{
    Garden g(diagram);
    const std::vector<Plants> vect = g.plants(student);

    if (vect.size() != 4U) {
        return {};  // returns an empty array if student not found
    }

    return {vect.at(0U), vect.at(1U), vect.at(2U), vect.at(3U)};
}

}  // namespace kindergarten_garden
