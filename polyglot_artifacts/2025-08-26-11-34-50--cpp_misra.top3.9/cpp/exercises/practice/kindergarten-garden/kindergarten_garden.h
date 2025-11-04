#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

using index_type = std::uint8_t;

enum class Plant {
    grass,
    clover,
    radishes,
    violets
};

class Garden {
public:
    explicit Garden(const std::string& diagram);

    std::vector<Plant> plants(const std::string& student) const;

// MISRA C++: static member functions should be defined as static in the class declaration
private:
    std::vector<std::string> rows_;
    static const std::vector<std::string> students_;
    static Plant char_to_plant(char c);
    static index_type student_index(const std::string& student);
};

// Provide a free function and alias for Plant to Plants for test compatibility
using Plants = Plant;
std::vector<Plant> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
