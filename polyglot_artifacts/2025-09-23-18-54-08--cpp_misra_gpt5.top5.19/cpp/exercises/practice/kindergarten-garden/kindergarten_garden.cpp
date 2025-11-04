#include "kindergarten_garden.h"

namespace kindergarten_garden {

const std::array<std::string, 12U> garden::kStudents{
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

garden::garden(const std::string& diagram) {
    const std::size_t newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        // Assume entire diagram is the first row; second row empty
        row1_ = diagram;
        row2_.clear();
    } else {
        row1_ = diagram.substr(0U, newline_pos);
        row2_ = diagram.substr(newline_pos + 1U);
    }
}

std::vector<plant> garden::plants(const std::string& student) const {
    const std::size_t idx = garden::student_index(student);
    const std::size_t start = (idx * 2U);

    std::vector<plant> result{};
    result.reserve(4U);

    if (start < row1_.size()) {
        const char c0 = row1_[start];
        result.push_back(garden::char_to_plant(c0));
    }
    if ((start + 1U) < row1_.size()) {
        const char c1 = row1_[start + 1U];
        result.push_back(garden::char_to_plant(c1));
    }
    if (start < row2_.size()) {
        const char c2 = row2_[start];
        result.push_back(garden::char_to_plant(c2));
    }
    if ((start + 1U) < row2_.size()) {
        const char c3 = row2_[start + 1U];
        result.push_back(garden::char_to_plant(c3));
    }

    return result;
}

// Free function wrapper expected by tests
std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student) {
    const garden g(diagram);
    const std::vector<plant> v = g.plants(student);

    std::array<Plants, 4U> out{
        plant::violets, plant::violets, plant::violets, plant::violets
    };

    if (!v.empty()) {
        const std::size_t n = (v.size() < 4U) ? v.size() : 4U;
        for (std::size_t i = 0U; i < n; ++i) {
            out[i] = v[i];
        }
    }

    return out;
}

plant garden::char_to_plant(const char c) {
    switch (c) {
        case 'G':
        {
            return plant::grass;
        }
        case 'C':
        {
            return plant::clover;
        }
        case 'R':
        {
            return plant::radishes;
        }
        case 'V':
        {
            return plant::violets;
        }
        default:
        {
            return plant::violets;
        }
    }
}

std::size_t garden::student_index(const std::string& student) {
    for (std::size_t i = 0U; i < kStudents.size(); ++i) {
        if (kStudents[i] == student) {
            return i;
        }
    }
    // If not found, default to first student position (Alice)
    return 0U;
}

}  // namespace kindergarten_garden
