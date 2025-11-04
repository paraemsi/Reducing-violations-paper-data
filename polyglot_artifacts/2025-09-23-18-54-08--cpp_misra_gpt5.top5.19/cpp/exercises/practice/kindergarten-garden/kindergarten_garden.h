#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class plant {
    clover,
    grass,
    radishes,
    violets
};
using Plants = plant;

// Free function API expected by tests
std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;

    static const std::array<std::string, 12U> kStudents;

    static plant char_to_plant(const char c);
    static std::size_t student_index(const std::string& student);
};

}  // namespace kindergarten_garden
