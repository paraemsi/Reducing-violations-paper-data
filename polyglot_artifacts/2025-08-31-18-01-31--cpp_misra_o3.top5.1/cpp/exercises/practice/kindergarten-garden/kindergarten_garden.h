#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <array>

#if __cplusplus >= 201703L
#define KDG_NODISCARD [[nodiscard]]
#else
#define KDG_NODISCARD
#endif

namespace kindergarten_garden {

enum class Plant {
    radishes,
    clover,
    grass,
    violets
};

using Plants = Plant;
using PlantArray = std::array<Plants, 4U>;

KDG_NODISCARD PlantArray plants(std::string_view diagram, std::string_view student);

class Garden {
public:
    explicit Garden(std::string_view diagram);
    Garden(std::string_view diagram, const std::vector<std::string>& students);

    KDG_NODISCARD std::vector<Plant> plants(std::string_view student) const;

private:
    void populate_assignments();

    std::string first_row_;
    std::string second_row_;
    std::vector<std::string> students_;
    std::unordered_map<std::string, std::vector<Plant>> assignments_;
};

}  // namespace kindergarten_garden
