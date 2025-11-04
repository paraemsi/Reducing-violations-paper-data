#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

const std::vector<std::string> Garden::students_ = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

Garden::Garden(const std::string& diagram)
{
    std::size_t start = 0U;
    std::size_t end = diagram.find('\n');
    while (end != std::string::npos) {
        rows_.push_back(diagram.substr(start, (end - start)));
        start = (end + 1U);
        end = diagram.find('\n', start);
    }
    if (start < diagram.size()) {
        rows_.push_back(diagram.substr(start));
    }
}

std::vector<Plant> Garden::plants(const std::string& student) const
{
    index_type idx = student_index(student);
    std::vector<Plant> result;
    for (const std::string& row : rows_) {
        for (index_type i = 0U; i < 2U; ++i) {
            std::size_t pos = static_cast<std::size_t>((2U * idx) + i);
            if (pos < row.size()) {
                result.push_back(char_to_plant(row[pos]));
            }
        }
    }
    return result;
}

Plant Garden::char_to_plant(char c)
{
    switch (c) {
        case 'G': return Plant::grass;
        case 'C': return Plant::clover;
        case 'R': return Plant::radishes;
        case 'V': return Plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

index_type Garden::student_index(const std::string& student)
{
    auto it = std::find(students_.begin(), students_.end(), student);
    if (it == students_.end()) {
        throw std::invalid_argument("Unknown student");
    }
    return static_cast<index_type>(it - students_.begin());
}

std::vector<Plant> plants(const std::string& diagram, const std::string& student)
{
    Garden garden(diagram);
    return garden.plants(student);
}

}  // namespace kindergarten_garden
