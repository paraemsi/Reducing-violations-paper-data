#include "kindergarten_garden.h"

#include <array>
#include <cstddef>
#include <string>
#include <vector>

namespace kindergarten_garden {

namespace {

// Map a diagram character to a plant enum.
// Only equality comparisons on char are used to respect the rule.
inline plant map_char_to_plant(char ch) {
    if (ch == 'G') {
        return plant::grass;
    } else {
        if (ch == 'C') {
            return plant::clover;
        } else {
            if (ch == 'R') {
                return plant::radishes;
            } else {
                if (ch == 'V') {
                    return plant::violets;
                } else {
                    // Fallback: treat any unknown marker as violets
                    return plant::violets;
                }
            }
        }
    }
}

inline Plants map_char_to_Plants(char ch) {
    if (ch == 'G') {
        return Plants::grass;
    } else {
        if (ch == 'C') {
            return Plants::clover;
        } else {
            if (ch == 'R') {
                return Plants::radishes;
            } else {
                // Default to violets for 'V' or any other non-specified value
                return Plants::violets;
            }
        }
    }
}

inline const std::vector<std::string>& default_students() {
    static const std::vector<std::string> names{
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"
    };
    return names;
}

inline std::size_t student_index(const std::string& name) {
    const std::vector<std::string>& names = default_students();
    for (std::size_t i = std::size_t{0}; i < names.size(); ++i) {
        if (names[i] == name) {
            return i;
        }
    }
    return names.size(); // not found marker
}

} // namespace

garden::garden(const std::string& diagram)
    : row1_(), row2_() {
    const std::string::size_type newline_pos = diagram.find('\n');
    if (newline_pos != std::string::npos) {
        row1_ = diagram.substr(std::string::size_type{0}, newline_pos);
        row2_ = diagram.substr(newline_pos + std::string::size_type{1});
    } else {
        row1_ = diagram;
        row2_.clear();
    }
}

std::vector<plant> garden::plants(const std::string& student) const {
    std::vector<plant> result{};
    result.reserve(std::size_t{4});
    const std::size_t idx = student_index(student);
    const std::vector<std::string>& names = default_students();

    if (idx >= names.size()) {
        return result;
    }

    const std::size_t pos = idx * std::size_t{2};

    if ((row1_.size() >= (pos + std::size_t{2}))) {
        result.push_back(map_char_to_plant(row1_[pos]));
        result.push_back(map_char_to_plant(row1_[pos + std::size_t{1}]));
    }

    if ((row2_.size() >= (pos + std::size_t{2}))) {
        result.push_back(map_char_to_plant(row2_[pos]));
        result.push_back(map_char_to_plant(row2_[pos + std::size_t{1}]));
    }

    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    std::array<Plants, 4> result{};

    std::string row1{};
    std::string row2{};

    const std::string::size_type newline_pos = diagram.find('\n');
    if (newline_pos != std::string::npos) {
        row1 = diagram.substr(std::string::size_type{0}, newline_pos);
        row2 = diagram.substr(newline_pos + std::string::size_type{1});
    } else {
        row1 = diagram;
        row2.clear();
    }

    const std::size_t idx = student_index(student);
    const std::vector<std::string>& names = default_students();
    if (idx >= names.size()) {
        return result;
    }

    const std::size_t pos = idx * std::size_t{2};

    if ((row1.size() >= (pos + std::size_t{2}))) {
        result[0] = map_char_to_Plants(row1[pos]);
        result[1] = map_char_to_Plants(row1[pos + std::size_t{1}]);
    }
    if ((row2.size() >= (pos + std::size_t{2}))) {
        result[2] = map_char_to_Plants(row2[pos]);
        result[3] = map_char_to_Plants(row2[pos + std::size_t{1}]);
    }

    return result;
}

}  // namespace kindergarten_garden
