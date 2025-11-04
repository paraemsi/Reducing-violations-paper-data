#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace kindergarten_garden {

namespace {
// Default list of students in alphabetical order.
std::vector<std::string> default_students() {
    return {"Alice",  "Bob",    "Charlie", "David",
            "Eve",    "Fred",   "Ginny",   "Harriet",
            "Ileana", "Joseph", "Kincaid", "Larry"};
}

// Split a two-line diagram into its two rows.
// Takes only the first two non-empty lines.
std::pair<std::string, std::string> split_rows(const std::string& diagram) {
    std::string first, second;
    std::size_t start = 0;
    while (start <= diagram.size()) {
        std::size_t end = diagram.find('\n', start);
        std::string line = diagram.substr(start, end == std::string::npos ? std::string::npos : end - start);
        if (!line.empty()) {
            if (first.empty()) {
                first = std::move(line);
            } else if (second.empty()) {
                second = std::move(line);
                break;
            }
        }
        if (end == std::string::npos) break;
        start = end + 1;
    }
    return {first, second};
}
}  // namespace

garden::garden(const std::string& diagram)
    : garden(diagram, default_students()) {}

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
    : row1_(), row2_(), students_(students) {
    std::sort(students_.begin(), students_.end());
    auto rows = split_rows(diagram);
    row1_ = std::move(rows.first);
    row2_ = std::move(rows.second);
}

std::vector<Plants> garden::plants(const std::string& student) const {
    std::vector<Plants> result;
    if (row1_.empty() || row2_.empty()) {
        return result;
    }
    std::size_t i = index_of(student);
    std::size_t pos = i * 2;

    // If the requested student's cups are out of bounds, return empty.
    if (pos + 1 >= row1_.size() || pos + 1 >= row2_.size()) {
        return result;
    }

    result.reserve(4);
    result.push_back(from_char(row1_[pos]));
    result.push_back(from_char(row1_[pos + 1]));
    result.push_back(from_char(row2_[pos]));
    result.push_back(from_char(row2_[pos + 1]));
    return result;
}

Plants garden::from_char(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

std::size_t garden::index_of(const std::string& student) const {
    auto it = std::find(students_.begin(), students_.end(), student);
    if (it == students_.end()) {
        // If student not found, return an index that will fail bounds check.
        return static_cast<std::size_t>(row1_.size()); 
    }
    return static_cast<std::size_t>(std::distance(students_.begin(), it));
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    auto v = g.plants(student);
    std::array<Plants, 4> out{};
    if (v.size() == 4) {
        out[0] = v[0];
        out[1] = v[1];
        out[2] = v[2];
        out[3] = v[3];
    }
    return out;
}

}  // namespace kindergarten_garden
