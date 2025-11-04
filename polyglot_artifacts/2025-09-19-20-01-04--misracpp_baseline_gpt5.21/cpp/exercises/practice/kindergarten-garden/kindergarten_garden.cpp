#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <string>
#include <utility>

namespace kindergarten_garden {

namespace {

constexpr std::array<const char*, 12> kStudents = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

inline plant code_to_plant(char c) {
    switch (c) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default:  return plant::grass;
    }
}

inline std::string strip_cr(std::string s) {
    s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
    return s;
}

inline std::pair<std::string, std::string> split_rows(const std::string& diagram) {
    auto newline = diagram.find('\n');
    if (newline == std::string::npos) {
        return {strip_cr(diagram), std::string{}};
    }
    std::string r1 = diagram.substr(0, newline);
    std::string r2 = diagram.substr(newline + 1);
    auto second_newline = r2.find('\n');
    if (second_newline != std::string::npos) {
        r2 = r2.substr(0, second_newline);
    }
    return {strip_cr(r1), strip_cr(r2)};
}

inline std::size_t student_index(const std::string& name) {
    for (std::size_t i = 0; i < kStudents.size(); ++i) {
        if (name == kStudents[i]) return i;
    }
    return kStudents.size();
}

}  // namespace

garden::garden(const std::string& diagram) {
    auto rows = split_rows(diagram);
    row1_ = std::move(rows.first);
    row2_ = std::move(rows.second);
}

std::vector<plant> garden::plants(const std::string& student) const {
    std::vector<plant> result;
    std::size_t idx = student_index(student);
    if (idx >= kStudents.size()) {
        return result;
    }
    std::size_t pos = idx * 2;
    if (row1_.size() < pos + 2 || row2_.size() < pos + 2) {
        return result;
    }
    result.reserve(4);
    result.push_back(code_to_plant(row1_[pos]));
    result.push_back(code_to_plant(row1_[pos + 1]));
    result.push_back(code_to_plant(row2_[pos]));
    result.push_back(code_to_plant(row2_[pos + 1]));
    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    std::array<Plants, 4> result{};
    auto rows = split_rows(diagram);
    std::size_t idx = student_index(student);
    if (idx >= kStudents.size()) {
        return result;
    }
    std::size_t pos = idx * 2;
    if (rows.first.size() < pos + 2 || rows.second.size() < pos + 2) {
        return result;
    }
    result[0] = code_to_plant(rows.first[pos]);
    result[1] = code_to_plant(rows.first[pos + 1]);
    result[2] = code_to_plant(rows.second[pos]);
    result[3] = code_to_plant(rows.second[pos + 1]);
    return result;
}

}  // namespace kindergarten_garden
