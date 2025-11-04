#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant {
    grass,
    clover,
    radishes,
    violets
};

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

class garden {
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = default_students());

    [[nodiscard]] std::vector<plant> plants(const std::string& student) const;

    // List of students in alphabetical order – accessible to tests and helpers
    static std::vector<std::string> default_students();

private:
    std::string row1_;
    std::string row2_;
    std::vector<std::string> students_;

    static plant decode_plant(char code);
};

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student,
                              const std::vector<std::string>& students = garden::default_students());

}  // namespace kindergarten_garden
