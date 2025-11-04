#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants : std::uint8_t {
    clover,
    grass,
    radishes,
    violets
};

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::string m_row1{};
    std::string m_row2{};
    std::unordered_map<std::string, std::size_t> m_index_by_student{};

    static Plants map_char_to_plant(const char c);
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
