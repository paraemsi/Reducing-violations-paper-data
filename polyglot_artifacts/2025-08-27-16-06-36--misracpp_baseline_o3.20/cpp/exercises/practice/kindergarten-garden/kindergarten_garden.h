#pragma once

#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

// Public enum required by tests
enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

// Internal alias to keep existing implementation code changes minimal
using Plant = Plants;

 // Convenience free-function expected by the tests
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::vector<Plant> plants(const std::string& student) const;

private:
    static const std::array<std::string, 12> default_students_;
    std::vector<std::string> students_;
    std::string row1_;
    std::string row2_;

    static Plant char_to_plant(char c);
};

}  // namespace kindergarten_garden
