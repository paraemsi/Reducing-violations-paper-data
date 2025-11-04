#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace kindergarten_garden {

garden::garden(const std::string& diagram, std::vector<std::string> students)
    : row1_{}, row2_{}, students_{std::move(students)} {
    auto pos = diagram.find('\n');
    if (pos == std::string::npos) {
        row1_ = diagram;
        row2_.clear();
    } else {
        row1_ = diagram.substr(0, pos);
        row2_ = diagram.substr(pos + 1);
    }

    trim_carriage_return(row1_);
    trim_carriage_return(row2_);

    std::sort(students_.begin(), students_.end());
}

void garden::trim_carriage_return(std::string& s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}

Plants garden::char_to_plant(char c) {
    switch (c) {
        case 'C': return Plants::clover;
        case 'G': return Plants::grass;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

std::vector<Plants> garden::plants(const std::string& student) const {
    std::vector<Plants> result;

    auto it = std::find(students_.begin(), students_.end(), student);
    if (it == students_.end()) {
        return result;
    }
    const std::size_t idx = static_cast<std::size_t>(std::distance(students_.begin(), it));
    const std::size_t col = idx * 2;

    auto add_from_row = [&](const std::string& row) {
        if (row.size() > col) {
            result.push_back(char_to_plant(row[col]));
        }
        if (row.size() > col + 1) {
            result.push_back(char_to_plant(row[col + 1]));
        }
    };

    add_from_row(row1_);
    add_from_row(row2_);

    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    using std::string;
    string row1, row2;
    auto pos = diagram.find('\n');
    if (pos == std::string::npos) {
        row1 = diagram;
        row2.clear();
    } else {
        row1 = diagram.substr(0, pos);
        row2 = diagram.substr(pos + 1);
    }
    // Trim potential CR from Windows line endings
    if (!row1.empty() && row1.back() == '\r') row1.pop_back();
    if (!row2.empty() && row2.back() == '\r') row2.pop_back();

    static const std::vector<std::string> students = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };

    auto it = std::find(students.begin(), students.end(), student);
    if (it == students.end()) {
        return {};
    }
    const std::size_t idx = static_cast<std::size_t>(std::distance(students.begin(), it));
    const std::size_t col = idx * 2;

    auto map = [](char c) -> Plants {
        switch (c) {
            case 'C': return Plants::clover;
            case 'G': return Plants::grass;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: throw std::invalid_argument("Unknown plant code");
        }
    };

    std::array<Plants, 4> out{
        map(row1.at(col)),
        map(row1.at(col + 1)),
        map(row2.at(col)),
        map(row2.at(col + 1))
    };
    return out;
}

}  // namespace kindergarten_garden
