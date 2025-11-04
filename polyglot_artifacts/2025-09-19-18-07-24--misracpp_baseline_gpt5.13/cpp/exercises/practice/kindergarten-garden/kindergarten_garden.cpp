#include "kindergarten_garden.h"

#include <algorithm>
#include <cstddef>
#include <array>
#include <vector>
#include <iterator>

namespace kindergarten_garden {

namespace {
const std::vector<std::string> kDefaultStudents = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"};
}  // namespace

garden::garden(const std::string& diagram)
    : garden(diagram, kDefaultStudents) {}

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
    : students_(students) {
    auto pos = diagram.find('\n');
    if (pos == std::string::npos) {
        // If the diagram is malformed (only one row), treat second row as empty.
        row1_ = diagram;
        row2_.clear();
    } else {
        row1_ = diagram.substr(0, pos);
        row2_ = diagram.substr(pos + 1);
    }

    // Ensure students are in alphabetical order as per the problem statement.
    std::sort(students_.begin(), students_.end());
}

std::vector<plant> garden::plants(const std::string& student) const {
    std::vector<plant> result;

    if (row2_.empty() || row1_.size() != row2_.size()) {
        // Malformed diagram; return empty result.
        return result;
    }

    const auto it = std::find(students_.begin(), students_.end(), student);
    if (it == students_.end()) {
        return result;
    }
    const std::size_t col =
        static_cast<std::size_t>(std::distance(students_.begin(), it)) * 2;

    if (col + 1 < row1_.size() && col + 1 < row2_.size()) {
        result.push_back(from_char(row1_[col]));
        result.push_back(from_char(row1_[col + 1]));
        result.push_back(from_char(row2_[col]));
        result.push_back(from_char(row2_[col + 1]));
    }

    return result;
}


plant garden::from_char(char c) {
    switch (c) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default:  return plant::grass;  // Default/fallback; input assumed valid.
    }
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

// Named accessors
std::vector<plant> garden::alice() const   { return plants("Alice"); }
std::vector<plant> garden::bob() const     { return plants("Bob"); }
std::vector<plant> garden::charlie() const { return plants("Charlie"); }
std::vector<plant> garden::david() const   { return plants("David"); }
std::vector<plant> garden::eve() const     { return plants("Eve"); }
std::vector<plant> garden::fred() const    { return plants("Fred"); }
std::vector<plant> garden::ginny() const   { return plants("Ginny"); }
std::vector<plant> garden::harriet() const { return plants("Harriet"); }
std::vector<plant> garden::ileana() const  { return plants("Ileana"); }
std::vector<plant> garden::joseph() const  { return plants("Joseph"); }
std::vector<plant> garden::kincaid() const { return plants("Kincaid"); }
std::vector<plant> garden::larry() const   { return plants("Larry"); }

}  // namespace kindergarten_garden
