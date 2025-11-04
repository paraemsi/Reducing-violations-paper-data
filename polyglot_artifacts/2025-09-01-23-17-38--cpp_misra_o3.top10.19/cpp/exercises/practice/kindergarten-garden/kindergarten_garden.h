#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace kindergarten_garden {

/* Enumeration describing all possible plants that can occur in a cup. */
enum class plant : std::uint8_t
{
    clover,
    grass,
    radishes,
    violets
};
 
/* Alias required by the tests to refer to the plant enumeration. */
using Plants = plant;
 
/* Forward declaration of the helper function translating a diagram symbol. */
plant symbol_to_plant(char symbol);
 
/* Convenience free function returning the four plants for a child
 * without explicitly constructing a garden object. */
std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& child,
                              std::vector<std::string> children = {});

/* Class representing an entire kindergarten garden. */
class garden
{
public:
    /* Default list of children in alphabetical order. */
    static const std::array<std::string, 12U> default_children;

    /* Construct a garden from its diagram and an optional custom child list. */
    explicit garden(const std::string& diagram,
                    std::vector<std::string> children = {});

    /* Retrieve the four plants that belong to the given child. */
    [[nodiscard]] std::vector<plant> plants(const std::string& child) const;

private:
    std::string m_row1 {};
    std::string m_row2 {};
    std::vector<std::string> m_children {};
};

}  // namespace kindergarten_garden
