#include "kindergarten_garden.h"
#include <utility>   // for std::move
#include <array>

namespace kindergarten_garden {

namespace {
/* Helper: split a diagram into two rows around the first '\n'. */
static void split_rows(std::string_view diagram,
                       std::string_view& row1,
                       std::string_view& row2)
{
    const std::size_t newline_pos{diagram.find('\n')};
    row1 = diagram.substr(0U, newline_pos);
    row2 = (newline_pos != std::string_view::npos)
               ? diagram.substr(newline_pos + 1U)
               : std::string_view{};
}
}  // namespace

/* static */ plant garden::char_to_plant(char code)
{
    /* Equality comparisons on character types are permitted;
     * avoid using the numeric value of the character (MISRA). */
    if (code == 'C') {
        return plant::clover;
    } else if (code == 'G') {
        return plant::grass;
    } else if (code == 'R') {
        return plant::radishes;
    } else if (code == 'V') {
        return plant::violets;
    } else {
        /* Undefined input – default to grass */
        return plant::grass;
    }
}

/* static */ std::vector<std::string> garden::default_students()
{
    return { "Alice",  "Bob",   "Charlie", "David",
             "Eve",    "Fred",  "Ginny",   "Harriet",
             "Ileana", "Joseph","Kincaid", "Larry" };
}

garden::garden(std::string_view diagram)
    : garden(diagram, default_students())
{
}

garden::garden(std::string_view diagram, std::vector<std::string> students)
{
    std::sort(students.begin(), students.end());

    std::string_view row1{};
    std::string_view row2{};
    split_rows(diagram, row1, row2);

    /* Each student has exactly two cups per row */
    const std::size_t cups_per_student{2U};
    const std::size_t expected_row_length{students.size() * cups_per_student};

    if ((row1.size() != expected_row_length) || (row2.size() != expected_row_length)) {
        /* Invalid diagram size – leave map empty */
        return;
    }

    for (std::size_t idx{0U}; idx < students.size(); ++idx) {
        const std::size_t col{idx * cups_per_student};

        std::vector<plant> assigned{
            char_to_plant(row1[col]),
            char_to_plant(row1[col + 1U]),
            char_to_plant(row2[col]),
            char_to_plant(row2[col + 1U])};

        student_plants_.emplace(students[idx], std::move(assigned));
    }
}

std::vector<plant> garden::plants(const std::string& student_name) const
{
    const auto it{student_plants_.find(student_name)};
    if (it != student_plants_.end()) {
        return it->second;
    } else {
        return {};
    }
}

/* Free helper expected by the tests */
std::array<plant, 4U> plants(std::string_view diagram,
                             std::string_view student_name)
{
    std::string_view row1{};
    std::string_view row2{};
    split_rows(diagram, row1, row2);

    const std::size_t cups_per_student{2U};
    const std::size_t num_students{(row1.size() / cups_per_student)};

    /* Build the list of students up to the required count */
    std::vector<std::string> students{
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"};
    if (num_students < students.size()) {
        students.resize(num_students);
    }

    kindergarten_garden::garden g(diagram, std::move(students));

    const std::vector<plant> vec{g.plants(std::string(student_name))};

    std::array<plant, 4U> result{};
    if (vec.size() == 4U) {
        for (std::size_t i{0U}; i < 4U; ++i) {
            result[i] = vec[i];
        }
    }
    return result;
}

}  // namespace kindergarten_garden
