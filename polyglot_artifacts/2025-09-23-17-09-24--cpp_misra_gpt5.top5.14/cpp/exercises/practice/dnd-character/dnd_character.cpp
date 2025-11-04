#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>

namespace dnd_character {

ability_score_t ability() {
    static thread_local std::mt19937 generator{
        []() {
            std::random_device device;
            const std::mt19937::result_type seed_value = device();
            return seed_value;
        }()
    };

    std::uniform_int_distribution<ability_score_t> distribution(ability_score_t{1}, ability_score_t{6});

    std::array<ability_score_t, 4U> rolls{};

    for (std::size_t i = std::size_t{0}; i < std::size_t{4}; ++i) {
        rolls[i] = distribution(generator);
    }

    std::sort(rolls.begin(), rolls.end());

    const ability_score_t total = ((rolls[1] + rolls[2]) + rolls[3]);

    return total;
}

ability_score_t modifier(const ability_score_t score) noexcept {
    const ability_score_t diff = (score - ability_score_t{10});
    ability_score_t mod = (diff / ability_score_t{2});
    if ((diff < ability_score_t{0}) && ((diff % ability_score_t{2}) != ability_score_t{0})) {
        mod = (mod - ability_score_t{1});
    }
    return mod;
}

Character::Character() noexcept
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(((ability_score_t{10}) + modifier(constitution))) {
}

}  // namespace dnd_character
