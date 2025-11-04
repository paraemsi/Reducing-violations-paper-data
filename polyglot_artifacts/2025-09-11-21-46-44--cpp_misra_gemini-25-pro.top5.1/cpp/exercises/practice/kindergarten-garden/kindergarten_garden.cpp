#include "kindergarten_garden.h"

#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>

namespace {

const std::array<std::string, 12> kChildren = {
    "Alice", "Bob",     "Charlie", "David",  "Eve",    "Fred",
    "Ginny", "Harriet", "Ileana",  "Joseph", "Kincaid", "Larry"};

kindergarten_garden::Plants char_to_plant(const char plant_char) {
    switch (plant_char) {
        case 'G': {
            return kindergarten_garden::Plants::grass;
        }
        case 'C': {
            return kindergarten_garden::Plants::clover;
        }
        case 'R': {
            return kindergarten_garden::Plants::radishes;
        }
        case 'V': {
            return kindergarten_garden::Plants::violets;
        }
        default: {
            throw std::invalid_argument("Invalid plant character");
        }
    }
}

std::size_t get_student_index(const std::string& student) {
    for (std::size_t i = 0; i < kChildren.size(); ++i) {
        if (kChildren[i] == student) {
            return i;
        }
    }
    throw std::invalid_argument("Unknown student");
}

class garden {
public:
    explicit garden(const std::string& diagram);
    std::array<kindergarten_garden::Plants, 4> plants(const std::string& student) const;

private:
    garden(const std::string& diagram, std::string::size_type newline_pos);
    static std::string::size_type find_newline(const std::string& diagram);

    const std::string row1_;
    const std::string row2_;
};

std::string::size_type garden::find_newline(const std::string& diagram) {
    const std::string::size_type pos = diagram.find('\n');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Diagram format error: missing newline.");
    }
    return pos;
}

garden::garden(const std::string& diagram)
    : garden(diagram, find_newline(diagram)) {}

garden::garden(const std::string& diagram, std::string::size_type newline_pos)
    : row1_{diagram.substr(0, newline_pos)},
      row2_{diagram.substr((newline_pos + 1U))} {}

std::array<kindergarten_garden::Plants, 4> garden::plants(const std::string& student) const {
    const std::size_t student_index = get_student_index(student);

    const std::size_t cup_index = (student_index * 2U);

    return {{char_to_plant(row1_.at(cup_index)),
             char_to_plant(row1_.at((cup_index + 1U))),
             char_to_plant(row2_.at(cup_index)),
             char_to_plant(row2_.at((cup_index + 1U)))}};
}

}  // namespace

namespace kindergarten_garden {

std::array<Plants, 4> plants(const std::string& diagram,
                               const std::string& student) {
    const garden g{diagram};
    return g.plants(student);
}

}  // namespace kindergarten_garden
