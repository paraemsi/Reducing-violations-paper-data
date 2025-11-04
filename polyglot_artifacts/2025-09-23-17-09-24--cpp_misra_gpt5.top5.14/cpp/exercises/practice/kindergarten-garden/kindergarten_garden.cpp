#include "kindergarten_garden.h"
#include <array>

namespace kindergarten_garden {

garden::garden(const std::string& diagram) {
    const std::size_t nl_pos = diagram.find('\n');
    if (nl_pos != std::string::npos) {
        row0_ = diagram.substr(0U, nl_pos);
        row1_ = diagram.substr((nl_pos + static_cast<std::size_t>(1)));
    } else {
        row0_ = diagram;
        row1_.clear();
    }
}

std::vector<Plants> garden::plants(const std::string& student) const {
    const std::vector<std::string>& names = students();

    std::size_t idx = static_cast<std::size_t>(0);
    bool found = false;
    for (std::size_t i = static_cast<std::size_t>(0); (i < names.size()); ++i) {
        if ((names[i] == student)) {
            idx = i;
            found = true;
            break;
        }
    }

    if (!found) {
        return {};
    }

    const std::size_t col = (idx * static_cast<std::size_t>(2));

    std::vector<Plants> result;
    result.reserve(static_cast<std::size_t>(4));

    if (row0_.size() >= (col + static_cast<std::size_t>(2))) {
        result.push_back(char_to_plant(row0_[col]));
        result.push_back(char_to_plant(row0_[(col + static_cast<std::size_t>(1))]));
    }

    if (row1_.size() >= (col + static_cast<std::size_t>(2))) {
        result.push_back(char_to_plant(row1_[col]));
        result.push_back(char_to_plant(row1_[(col + static_cast<std::size_t>(1))]));
    }

    return result;
}

const std::vector<std::string>& garden::students() {
    static const std::vector<std::string> names = {
        "Alice",
        "Bob",
        "Charlie",
        "David",
        "Eve",
        "Fred",
        "Ginny",
        "Harriet",
        "Ileana",
        "Joseph",
        "Kincaid",
        "Larry"
    };
    return names;
}

Plants garden::char_to_plant(const char c) {
    if (c == 'G') {
        return Plants::grass;
    } else if (c == 'C') {
        return Plants::clover;
    } else if (c == 'R') {
        return Plants::radishes;
    } else if (c == 'V') {
        return Plants::violets;
    } else {
        return Plants::grass;
    }
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    const std::vector<Plants> v = g.plants(student);

    std::array<Plants, 4> out = { Plants::grass, Plants::grass, Plants::grass, Plants::grass };

    if (v.size() >= static_cast<std::size_t>(4)) {
        out[static_cast<std::size_t>(0)] = v[static_cast<std::size_t>(0)];
        out[static_cast<std::size_t>(1)] = v[static_cast<std::size_t>(1)];
        out[static_cast<std::size_t>(2)] = v[static_cast<std::size_t>(2)];
        out[static_cast<std::size_t>(3)] = v[static_cast<std::size_t>(3)];
    } else if (v.size() == static_cast<std::size_t>(2)) {
        out[static_cast<std::size_t>(0)] = v[static_cast<std::size_t>(0)];
        out[static_cast<std::size_t>(1)] = v[static_cast<std::size_t>(1)];
    } else {
        // Leave defaults if insufficient data
    }

    return out;
}

}  // namespace kindergarten_garden
