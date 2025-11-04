#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <array>
#include <cstdint>
#include <cstddef>

namespace kindergarten_garden {

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

class garden {
public:
    explicit garden(std::string_view diagram,
                    std::vector<std::string> students = default_students());

    [[nodiscard]] std::vector<Plants> plants(const std::string& student) const;

private:
    static std::vector<std::string> default_students();
    static Plants char_to_plant(char cup);

    std::unordered_map<std::string, std::vector<Plants>> assignments_;
};

std::array<Plants, 4U> plants(std::string_view diagram,
                              std::string_view student,
                              std::vector<std::string> students = {});

}  // namespace kindergarten_garden
