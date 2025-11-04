#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class Plants {
    clover,
    grass,
    radishes,
    violets
};

// Default list of students in alphabetical order.
std::vector<std::string> default_students();
std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram, std::vector<std::string> students = default_students());
    std::vector<Plants> plants(const std::string& student) const;

private:
    std::map<std::string, std::vector<Plants>> roster_;
};

}  // namespace kindergarten_garden
