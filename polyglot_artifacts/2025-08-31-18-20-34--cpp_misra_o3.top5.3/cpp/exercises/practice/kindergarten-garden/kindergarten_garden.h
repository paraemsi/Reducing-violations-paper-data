#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <array>

namespace kindergarten_garden {

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

/* Convenience free-function used by the tests */
[[nodiscard]] std::array<Plants, 4U> plants(const std::string& diagram,
                                            const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram, std::vector<std::string> students = {});

    [[nodiscard]] std::array<Plants, 4U> plants(const std::string& student) const;

private:
    std::vector<std::string> m_students;
    std::string m_row1;
    std::string m_row2;

    static Plants char_to_plant(char symbol);
};

}  // namespace kindergarten_garden
