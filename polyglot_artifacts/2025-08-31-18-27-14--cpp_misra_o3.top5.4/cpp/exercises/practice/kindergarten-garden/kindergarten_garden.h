#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <cstdint>

namespace kindergarten_garden {

enum class plant
{
    clover,
    grass,
    radishes,
    violets
};

using Plants = plant;

class garden
{
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = {});

    [[nodiscard]] std::array<plant, 4U> plants(const std::string& student) const;

private:
    std::unordered_map<std::string, std::array<plant, 4U>> m_student_plants {};

    static std::vector<std::string> default_students();
    static plant char_to_plant(char plant_code);
};

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student,
                              const std::vector<std::string>& students = {});

}  // namespace kindergarten_garden
