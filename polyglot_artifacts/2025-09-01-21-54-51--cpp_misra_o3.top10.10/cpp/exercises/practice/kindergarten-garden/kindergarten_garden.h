#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace kindergarten_garden {

enum class Plants
{
    radishes,
    clover,
    grass,
    violets
};

class garden
{
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = {});

    [[nodiscard]] std::vector<Plants> plants(const std::string& student) const;

private:
    using index_t = std::size_t;

    static Plants decodePlant(char code);

    std::unordered_map<std::string, std::vector<Plants>> assignments_;
};

[[nodiscard]] std::array<Plants, 4U> plants(const std::string& diagram,
                                            const std::string& student);

}  // namespace kindergarten_garden
