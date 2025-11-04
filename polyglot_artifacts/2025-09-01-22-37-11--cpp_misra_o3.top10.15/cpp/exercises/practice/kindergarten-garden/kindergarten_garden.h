#pragma once

#include <cstdint>
#include <string>
#include <string_view>
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
    static const std::vector<std::string>& default_students();

    explicit garden(std::string_view diagram,
                    const std::vector<std::string>& students = default_students());

    [[nodiscard]] std::vector<Plants> plants(std::string_view student) const;

private:
    std::unordered_map<std::string, std::vector<Plants>> m_assignments;
};

[[nodiscard]] std::array<Plants, 4U> plants(std::string_view diagram, std::string_view student);

}  // namespace kindergarten_garden
