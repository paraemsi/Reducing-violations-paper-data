#pragma once

#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <cstddef>   // for std::size_t
#include <array>

namespace kindergarten_garden {

enum class Plants : std::uint8_t {
    grass,
    clover,
    radishes,
    violets
};

class Garden {
public:
    explicit Garden(const std::string& diagram,
                    const std::vector<std::string>& students = { "Alice", "Bob", "Charlie", "David",
                                                                "Eve", "Fred", "Ginny", "Harriet",
                                                                "Ileana", "Joseph", "Kincaid", "Larry" });

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::map<std::string, std::vector<Plants>> m_student_plants;
};

/* Helper free-function expected by the tests */
std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
