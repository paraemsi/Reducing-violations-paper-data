#include "kindergarten_garden.h"

#include <array>
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace kindergarten_garden {

namespace {
    plant to_plant(const char code) {
        switch (code) {
            case 'G':
                return plant::grass;
            case 'C':
                return plant::clover;
            case 'R':
                return plant::radishes;
            case 'V':
                return plant::violets;
            default:
                return plant::grass;
        }
    }

    static constexpr std::array<std::string_view, 12U> kStudents = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
}  // anonymous namespace

garden::garden(const std::string& diagram) : row0_(), row1_() {
    const std::size_t nl = diagram.find('\n');
    if ((nl != std::string::npos)) {
        row0_ = diagram.substr(static_cast<std::size_t>(0), nl);
        row1_ = diagram.substr((nl + static_cast<std::size_t>(1)));
    } else {
        row0_ = diagram;
        row1_.clear();
    }
}

std::vector<plant> garden::plants(const std::string& student) const {
    std::size_t idx = static_cast<std::size_t>(0);
    bool found = false;

    for (std::size_t i = static_cast<std::size_t>(0); (i < kStudents.size()); ++i) {
        if ((student == kStudents[i])) {
            idx = i;
            found = true;
            break;
        } else {
            // continue
        }
    }

    std::vector<plant> result;
    result.reserve(static_cast<std::size_t>(4));

    if ((found == false)) {
        return result;
    } else {
        const std::size_t start = (idx * static_cast<std::size_t>(2));

        if (((row0_.size() <= (start + static_cast<std::size_t>(1))) || (row1_.size() <= (start + static_cast<std::size_t>(1))))) {
            return result;
        } else {
            const char c0 = row0_.at(start);
            const char c1 = row0_.at((start + static_cast<std::size_t>(1)));
            const char c2 = row1_.at(start);
            const char c3 = row1_.at((start + static_cast<std::size_t>(1)));

            result.push_back(to_plant(c0));
            result.push_back(to_plant(c1));
            result.push_back(to_plant(c2));
            result.push_back(to_plant(c3));

            return result;
        }
    }
}

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    const std::vector<plant> v = g.plants(student);

    std::array<Plants, 4U> out{};
    if ((v.size() == static_cast<std::size_t>(4))) {
        out[static_cast<std::size_t>(0)] = v[static_cast<std::size_t>(0)];
        out[static_cast<std::size_t>(1)] = v[static_cast<std::size_t>(1)];
        out[static_cast<std::size_t>(2)] = v[static_cast<std::size_t>(2)];
        out[static_cast<std::size_t>(3)] = v[static_cast<std::size_t>(3)];
    } else {
        // no assignment; return default-initialized array
    }

    return out;
}

}  // namespace kindergarten_garden
