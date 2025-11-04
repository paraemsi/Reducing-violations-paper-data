#pragma once

#include <string>
#include <vector>
#include <array>
#include <cstddef>

namespace kindergarten_garden {

enum class plant { clover, grass, radishes, violets };
using Plants = plant;

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::vector<std::string> rows_;
    std::vector<std::string> students_;

    static const std::vector<std::string>& default_students();
    static std::vector<std::string> normalize_students(std::vector<std::string> students);
    static plant to_plant(char code);
    std::size_t index_for_student(const std::string& name) const;
};

// Free function API expected by tests
std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
