#include "kindergarten_garden.h"

#include <algorithm>
#include <cstddef>
#include <array>
#include <utility>

namespace kindergarten_garden {

std::vector<std::string> default_students() {
    return {
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"
    };
}

plant garden::char_to_plant(char c) {
    switch (c) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default:  return plant::grass;  // Fallback; input is assumed valid per exercise
    }
}

garden::garden(const std::string& diagram, std::vector<std::string> students) {
    // Expect exactly two rows separated by a single newline.
    auto nl = diagram.find('\n');
    std::string row1 = diagram.substr(0, nl);
    std::string row2 = (nl == std::string::npos) ? std::string{} : diagram.substr(nl + 1);

    // Ensure students are in alphabetical order.
    std::sort(students.begin(), students.end());

    for (std::size_t i = 0; i < students.size(); ++i) {
        std::size_t col = i * 2;
        std::vector<plant> ps;
        if (row1.size() >= col + 2 && row2.size() >= col + 2) {
            ps.reserve(4);
            ps.push_back(char_to_plant(row1[col]));
            ps.push_back(char_to_plant(row1[col + 1]));
            ps.push_back(char_to_plant(row2[col]));
            ps.push_back(char_to_plant(row2[col + 1]));
        }
        assignments_.emplace(students[i], std::move(ps));
    }
}

std::vector<plant> garden::plants(const std::string& student) const {
    auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        return {};
    }
    return it->second;
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
