#pragma once

#include <array>
#include <cstdint>
#include <cstddef>
#include <map>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class Plants : std::uint8_t {
    grass,
    clover,
    radishes,
    violets
};

class garden {
public:
    explicit garden(const std::string& diagram);

    [[nodiscard]] std::array<Plants, 4U> plants(const std::string& student) const;

private:
    static const std::array<const char*, 12U> student_names;

    std::map<std::string, std::array<Plants, 4U>> assignments_;

    static Plants char_to_plant(char ch);
};

[[nodiscard]] std::array<Plants, 4U> plants(const std::string& diagram,
                                            const std::string& student);

}  // namespace kindergarten_garden
