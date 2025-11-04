#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include <array>
#include <iterator>

namespace {
std::vector<std::string> split_rows(const std::string& diagram) {
    std::vector<std::string> rows;
    std::string current;
    for (char ch : diagram) {
        if (ch == '\r') continue;           // tolerate CRLF
        if (ch == '\n') {
            rows.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    if (!current.empty()) {
        rows.push_back(current);
    }

    // If the diagram began with a newline, drop the initial empty row.
    if (!rows.empty() && rows.front().empty() && rows.size() >= 2) {
        rows.erase(rows.begin());
    }

    if (rows.size() != 2) {
        throw std::invalid_argument("diagram must consist of exactly two rows");
    }
    if (rows[0].size() != rows[1].size() || (rows[0].size() % 2) != 0) {
        throw std::invalid_argument("rows must be the same even length");
    }

    return rows;
}

std::vector<std::string> default_students_list() {
    return {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
}
}  // anonymous namespace

namespace kindergarten_garden {

const std::vector<std::string>& garden::default_students() {
    static const std::vector<std::string> defaults = [] {
        return default_students_list();
    }();
    return defaults;
}

std::vector<std::string> garden::normalize_students(std::vector<std::string> students) {
    std::sort(students.begin(), students.end());
    return students;
}

plant garden::to_plant(char code) {
    switch (code) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default: throw std::invalid_argument("unknown plant code");
    }
}

garden::garden(const std::string& diagram)
: rows_(split_rows(diagram)), students_(default_students()) {}

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
: rows_(split_rows(diagram)), students_(normalize_students(students)) {}

std::size_t garden::index_for_student(const std::string& name) const {
    auto it = std::find(students_.begin(), students_.end(), name);
    if (it == students_.end()) {
        throw std::invalid_argument("student not found");
    }
    return static_cast<std::size_t>(std::distance(students_.begin(), it));
}

std::vector<plant> garden::plants(const std::string& student) const {
    std::vector<plant> result;
    const std::size_t idx = index_for_student(student) * 2;
    result.reserve(4);
    result.push_back(to_plant(rows_[0][idx]));
    result.push_back(to_plant(rows_[0][idx + 1]));
    result.push_back(to_plant(rows_[1][idx]));
    result.push_back(to_plant(rows_[1][idx + 1]));
    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    auto v = g.plants(student);
    if (v.size() != 4) {
        throw std::logic_error("expected exactly four plants for student");
    }
    return { v[0], v[1], v[2], v[3] };
}

}  // namespace kindergarten_garden
