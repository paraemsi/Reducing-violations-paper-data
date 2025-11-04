#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace kindergarten_garden {

namespace {

constexpr std::array<const char*, 12> kStudents{
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

inline plant decode(char c) {
    switch (c) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

inline Plants decode_to_Plants(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

} // namespace

garden::garden(const std::string& diagram) {
    auto nl = diagram.find('\n');
    if (nl == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    }
    row1_ = diagram.substr(0, nl);
    row2_ = diagram.substr(nl + 1);
}

std::vector<plant> garden::plants(const std::string& student) const {
    auto it = std::find_if(kStudents.begin(), kStudents.end(),
                           [&](const char* s) { return student == s; });
    if (it == kStudents.end()) {
        return {};
    }

    std::size_t idx = static_cast<std::size_t>(std::distance(kStudents.begin(), it));
    std::size_t start = idx * 2;

    if (row1_.size() < start + 2 || row2_.size() < start + 2) {
        throw std::out_of_range("Diagram does not have enough cups for the requested student");
    }

    std::vector<plant> result;
    result.reserve(4);
    result.push_back(decode(row1_[start]));
    result.push_back(decode(row1_[start + 1]));
    result.push_back(decode(row2_[start]));
    result.push_back(decode(row2_[start + 1]));
    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    auto nl = diagram.find('\n');
    if (nl == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    }
    const std::string row1 = diagram.substr(0, nl);
    const std::string row2 = diagram.substr(nl + 1);

    auto it = std::find_if(kStudents.begin(), kStudents.end(),
                           [&](const char* s) { return student == s; });
    if (it == kStudents.end()) {
        return { }; // empty-initialized; tests might not hit this path
    }

    std::size_t idx = static_cast<std::size_t>(std::distance(kStudents.begin(), it));
    std::size_t start = idx * 2;

    if (row1.size() < start + 2 || row2.size() < start + 2) {
        throw std::out_of_range("Diagram does not have enough cups for the requested student");
    }

    return { decode_to_Plants(row1[start]),
             decode_to_Plants(row1[start + 1]),
             decode_to_Plants(row2[start]),
             decode_to_Plants(row2[start + 1]) };
}

}  // namespace kindergarten_garden
