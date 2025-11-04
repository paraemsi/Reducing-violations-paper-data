#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <stdexcept>

namespace kindergarten_garden {

namespace
{
constexpr std::array<const char*, 12U> default_student_names {
    "Alice",   "Bob",     "Charlie", "David",
    "Eve",     "Fred",    "Ginny",   "Harriet",
    "Ileana",  "Joseph",  "Kincaid", "Larry"
};

std::vector<std::string> build_default()
{
    return std::vector<std::string>(default_student_names.begin(),
                                    default_student_names.end());
}
}  // unnamed namespace

std::vector<std::string> garden::default_students()
{
    return build_default();
}

plant garden::char_to_plant(char plant_code)
{
    if (plant_code == 'G') {
        return plant::grass;
    } else if (plant_code == 'C') {
        return plant::clover;
    } else if (plant_code == 'R') {
        return plant::radishes;
    } else if (plant_code == 'V') {
        return plant::violets;
    } else {
        /* An unexpected code is a programming error – make it visible. */
        throw std::invalid_argument("Unknown plant code");
    }
}

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
{
    std::vector<std::string> student_list = students;
    if (student_list.empty()) {
        student_list = default_students();
    }

    std::sort(student_list.begin(), student_list.end());

    /* Split the diagram into two rows. */
    std::string row1;
    std::string row2;
    {
        const std::string::size_type newline_pos = diagram.find('\n');
        if (newline_pos == std::string::npos) {
            row1 = diagram;
            row2 = "";
        } else {
            row1 = diagram.substr(0U, newline_pos);
            row2 = diagram.substr(newline_pos + 1U);
        }
    }

    constexpr std::size_t cups_per_student = 2U;

    const std::size_t students_in_diagram =
        row1.length() / cups_per_student;

    std::size_t total_students = student_list.size();
    if (total_students > students_in_diagram) {
        total_students = students_in_diagram;
    }

    for (std::size_t i = 0U; i < total_students; ++i) {
        const std::size_t offset = i * cups_per_student;

        std::array<plant, 4U> plants_for_student {};

        plants_for_student[0U] = char_to_plant(row1.at(offset));
        plants_for_student[1U] = char_to_plant(row1.at(offset + 1U));

        if (row2.length() >= (offset + 2U)) {
            plants_for_student[2U] = char_to_plant(row2.at(offset));
            plants_for_student[3U] = char_to_plant(row2.at(offset + 1U));
        }

        m_student_plants.emplace(student_list.at(i), plants_for_student);
    }
}

std::array<plant, 4U> garden::plants(const std::string& student) const
{
    const auto it = m_student_plants.find(student);
    if (it != m_student_plants.end()) {
        return it->second;
    }

    return {};
}

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student,
                              const std::vector<std::string>& students)
{
    const garden g(diagram, students);
    return g.plants(student);
}

}  // namespace kindergarten_garden
