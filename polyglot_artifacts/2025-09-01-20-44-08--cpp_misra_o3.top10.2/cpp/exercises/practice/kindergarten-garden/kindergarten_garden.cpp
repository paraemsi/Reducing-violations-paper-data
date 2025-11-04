#include "kindergarten_garden.h"

#include <stdexcept>
#include <cstddef>

namespace kindergarten_garden {

const std::array<const char*, 12U> garden::student_names{
    {"Alice",  "Bob",   "Charlie", "David",
     "Eve",    "Fred",  "Ginny",   "Harriet",
     "Ileana", "Joseph","Kincaid", "Larry"}};

namespace {

std::vector<std::string> split_rows(const std::string& diagram)
{
    std::vector<std::string> rows;
    std::string current;
    for(char ch : diagram) {
        if(ch == '\n') {
            rows.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    rows.push_back(current);
    return rows;
}

}  // unnamed namespace

garden::garden(const std::string& diagram)
{
    const std::vector<std::string> rows{split_rows(diagram)};

    if((rows.size() != 2U) || (rows[0U].length() != rows[1U].length())) {
        throw std::invalid_argument("diagram must contain exactly two equal-length rows");
    }

    if((rows[0U].length() % 2U) != 0U) {
        throw std::invalid_argument("each diagram row must contain an even number of cups");
    }

    const std::size_t num_students{rows[0U].length() / 2U};

    for(std::size_t idx = 0U; idx < num_students; ++idx) {
        const std::size_t pos{idx * 2U};

        std::array<Plants, 4U> student_plants{
            {char_to_plant(rows[0U][pos]),
             char_to_plant(rows[0U][(pos + 1U)]),
             char_to_plant(rows[1U][pos]),
             char_to_plant(rows[1U][(pos + 1U)])}};

        assignments_.emplace(std::string{student_names[idx]}, student_plants);
    }
}

std::array<Plants, 4U> garden::plants(const std::string& student) const
{
    const auto it{assignments_.find(student)};
    if(it == assignments_.end()) {
        throw std::out_of_range("unknown student");
    }

    return it->second;
}

Plants garden::char_to_plant(char ch)
{
    switch(ch) {
        case 'G':
            return Plants::grass;
        case 'C':
            return Plants::clover;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            throw std::invalid_argument("invalid plant character");
    }
}

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student)
{
    const garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
