#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant {
    clover,
    grass,
    radishes,
    violets
};

using Plants = plant;

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student);

class kindergarten {
public:
    // Declare default_students() before it is referenced by the constructor’s
    // default-argument expression to satisfy the one-pass lookup rules.
    static std::vector<std::string> default_students();

    explicit kindergarten(const std::string& diagram,
                          const std::vector<std::string>& students = default_students());

    [[nodiscard]] std::vector<plant> plants(const std::string& student) const;

private:
    static plant to_plant(char code);

    std::map<std::string, std::vector<plant>> m_lookup{};
};

}  // namespace kindergarten_garden
