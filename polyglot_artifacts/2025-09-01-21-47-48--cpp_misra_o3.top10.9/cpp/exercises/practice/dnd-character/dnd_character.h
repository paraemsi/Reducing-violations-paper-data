#pragma once

#include <cstdint>

namespace dnd_character {

class DndCharacter
{
public:
    DndCharacter();

    static std::int32_t ability() noexcept;
    static std::int32_t modifier(std::int32_t score) noexcept;


    [[nodiscard]] std::int32_t strength() const noexcept;
    [[nodiscard]] std::int32_t dexterity() const noexcept;
    [[nodiscard]] std::int32_t constitution() const noexcept;
    [[nodiscard]] std::int32_t intelligence() const noexcept;
    [[nodiscard]] std::int32_t wisdom() const noexcept;
    [[nodiscard]] std::int32_t charisma() const noexcept;
    [[nodiscard]] std::int32_t hitpoints() const noexcept;

private:

    std::int32_t m_strength;
    std::int32_t m_dexterity;
    std::int32_t m_constitution;
    std::int32_t m_intelligence;
    std::int32_t m_wisdom;
    std::int32_t m_charisma;
    std::int32_t m_hitpoints;
};

std::int32_t ability() noexcept;
std::int32_t modifier(std::int32_t score) noexcept;

struct Character
{
    std::int32_t strength;
    std::int32_t dexterity;
    std::int32_t constitution;
    std::int32_t intelligence;
    std::int32_t wisdom;
    std::int32_t charisma;
    std::int32_t hitpoints;

    Character()
        : strength{ability()},
          dexterity{ability()},
          constitution{ability()},
          intelligence{ability()},
          wisdom{ability()},
          charisma{ability()},
          hitpoints{10 + modifier(constitution)}
    {
    }
};

}  // namespace dnd_character
