#pragma once

#include <cstdint>

namespace dnd_character {

// Roll a single ability score (4d6, drop the lowest, sum the rest).
auto ability() -> std::int32_t;

auto modifier(std::int32_t score) noexcept -> std::int32_t;

// Representation of a freshly-generated D&D character as required by the tests.
struct Character
{
    std::int32_t strength{};
    std::int32_t dexterity{};
    std::int32_t constitution{};
    std::int32_t intelligence{};
    std::int32_t wisdom{};
    std::int32_t charisma{};
    std::int32_t hitpoints{};

    Character();
};

// Representation of a freshly-generated D&D character.
class character
{
public:
    character();

    [[nodiscard]] auto strength() const noexcept -> std::int32_t;
    [[nodiscard]] auto dexterity() const noexcept -> std::int32_t;
    [[nodiscard]] auto constitution() const noexcept -> std::int32_t;
    [[nodiscard]] auto intelligence() const noexcept -> std::int32_t;
    [[nodiscard]] auto wisdom() const noexcept -> std::int32_t;
    [[nodiscard]] auto charisma() const noexcept -> std::int32_t;

    [[nodiscard]] static auto modifier(std::int32_t score) noexcept -> std::int32_t;
    [[nodiscard]] auto hitpoints() const noexcept -> std::int32_t;

private:
    std::int32_t m_strength{};
    std::int32_t m_dexterity{};
    std::int32_t m_constitution{};
    std::int32_t m_intelligence{};
    std::int32_t m_wisdom{};
    std::int32_t m_charisma{};
};

}  // namespace dnd_character
