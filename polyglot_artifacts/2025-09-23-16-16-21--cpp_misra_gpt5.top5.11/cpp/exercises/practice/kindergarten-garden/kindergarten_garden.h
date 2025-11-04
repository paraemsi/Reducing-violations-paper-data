#pragma once

#include <cstddef>
#include <cstdint>
#include <array>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class plant {
    clover,
    grass,
    radishes,
    violets
};

enum class Plants {
    clover,
    grass,
    radishes,
    violets
};

// Free function API expected by tests.
std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<plant> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;

    static plant to_plant(const char code);
    static std::size_t student_index(const std::string& student);
};

}  // namespace kindergarten_garden
