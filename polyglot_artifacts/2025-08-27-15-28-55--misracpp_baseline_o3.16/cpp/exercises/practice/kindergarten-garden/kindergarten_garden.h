#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <array>

namespace kindergarten_garden {

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

class garden {
public:
    garden(std::string_view diagram,
           std::vector<std::string> students = { "Alice", "Bob", "Charlie", "David",
                                                 "Eve", "Fred", "Ginny", "Harriet",
                                                 "Ileana", "Joseph", "Kincaid", "Larry" });

    const std::vector<Plants>& plants(std::string_view student) const;

private:
    std::unordered_map<std::string, std::vector<Plants>> assignments_;
};

// Convenience helper function expected by the tests
std::array<Plants, 4> plants(std::string_view diagram, std::string_view student);

}  // namespace kindergarten_garden
