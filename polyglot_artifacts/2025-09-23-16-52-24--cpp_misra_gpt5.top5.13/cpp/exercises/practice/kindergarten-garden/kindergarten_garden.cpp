#include "kindergarten_garden.h"

#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace kindergarten_garden {

namespace {
constexpr std::array<const char*, 12U> kRoster = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};
}  // namespace

garden::garden(const std::string& diagram)
{
    std::string local = diagram;

    if ((!local.empty()) && (local.front() == '\n')) {
        local.erase(static_cast<std::size_t>(0), static_cast<std::size_t>(1));
    }

    const std::size_t split_pos = local.find('\n');
    if (split_pos == std::string::npos) {
        throw std::invalid_argument("diagram must contain two rows separated by a newline");
    }

    row1_ = local.substr(static_cast<std::size_t>(0), split_pos);
    row2_ = local.substr(split_pos + static_cast<std::size_t>(1));

    if (row1_.size() != row2_.size()) {
        throw std::invalid_argument("rows must be the same length");
    }
    if (((row1_.size() % static_cast<std::size_t>(2)) != static_cast<std::size_t>(0))) {
        throw std::invalid_argument("each row must have an even number of cups");
    }
}

std::vector<plant> garden::plants(const std::string& student) const
{
    const std::size_t idx = student_index(student);
    const std::size_t pos = (idx * static_cast<std::size_t>(2));

    if ((row1_.size() < (pos + static_cast<std::size_t>(2))) || (row2_.size() < (pos + static_cast<std::size_t>(2)))) {
        throw std::out_of_range("not enough cups for the requested student");
    }

    std::vector<plant> result{};
    result.reserve(static_cast<std::size_t>(4));

    result.push_back(char_to_plant(row1_[pos]));
    result.push_back(char_to_plant(row1_[pos + static_cast<std::size_t>(1)]));
    result.push_back(char_to_plant(row2_[pos]));
    result.push_back(char_to_plant(row2_[pos + static_cast<std::size_t>(1)]));

    return result;
}

std::size_t garden::student_index(const std::string& student)
{
    for (std::size_t i = 0; i < kRoster.size(); ++i) {
        if (student == kRoster[i]) {
            return i;
        }
    }
    throw std::invalid_argument("unknown student name");
}

plant garden::char_to_plant(char c)
{
    if (c == 'G') {
        return plant::grass;
    } else if (c == 'C') {
        return plant::clover;
    } else if (c == 'R') {
        return plant::radishes;
    } else if (c == 'V') {
        return plant::violets;
    } else {
        throw std::invalid_argument("unknown plant code");
    }
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student)
{
    const garden g(diagram);
    const std::vector<plant> vp = g.plants(student);

    std::array<Plants, 4> out{};

    const auto to_Plants = [](const plant p_in) -> Plants {
        switch (p_in) {
            case plant::clover:
                return Plants::clover;
            case plant::grass:
                return Plants::grass;
            case plant::radishes:
                return Plants::radishes;
            case plant::violets:
                return Plants::violets;
            default:
                throw std::invalid_argument("invalid plant enum");
        }
    };

    out[0] = to_Plants(vp[0]);
    out[1] = to_Plants(vp[1]);
    out[2] = to_Plants(vp[2]);
    out[3] = to_Plants(vp[3]);

    return out;
}

}  // namespace kindergarten_garden
