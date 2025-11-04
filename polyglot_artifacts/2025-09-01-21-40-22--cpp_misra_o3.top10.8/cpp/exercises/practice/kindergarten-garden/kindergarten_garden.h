#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

namespace kindergarten_garden {

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

class garden {
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = {});

    std::vector<Plants> plants(const std::string& student) const;

private:
    static const std::array<std::string, 12U> default_students;

    static Plants char_to_plant(char code);

    std::unordered_map<std::string, std::vector<Plants>> m_student_plants;
};
 
std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student,
                              const std::vector<std::string>& students = {});
 
}  // namespace kindergarten_garden
