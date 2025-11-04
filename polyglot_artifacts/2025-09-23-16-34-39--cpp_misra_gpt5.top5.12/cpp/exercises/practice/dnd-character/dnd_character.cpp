#include "dnd_character.h"

#include <cstdint>
#include <random>

namespace dnd_character {

namespace {
    std::mt19937& rng() {
        thread_local static std::mt19937 engine{std::random_device{}()};
        return engine;
    }

    std::int32_t roll_die(std::int32_t sides) {
        std::uniform_int_distribution<std::int32_t> dist(static_cast<std::int32_t>(1), sides);
        return dist(rng());
    }
}  // namespace

std::int32_t ability() noexcept {
    std::int32_t sum = static_cast<std::int32_t>(0);
    std::int32_t minv = static_cast<std::int32_t>(7);

    std::int32_t i = static_cast<std::int32_t>(0);
    while ((i < static_cast<std::int32_t>(4))) {
        const std::int32_t roll = roll_die(static_cast<std::int32_t>(6));
        sum = (sum + roll);
        if ((roll < minv)) {
            minv = roll;
        }
        i = (i + static_cast<std::int32_t>(1));
    }

    return (sum - minv);
}

std::int32_t modifier(std::int32_t score) noexcept {
    const std::int32_t n = (score - static_cast<std::int32_t>(10));
    if ((n >= static_cast<std::int32_t>(0))) {
        return (n / static_cast<std::int32_t>(2));
    } else {
        const std::int32_t pos = -n;
        const std::int32_t ceil_div = ((pos + static_cast<std::int32_t>(1)) / static_cast<std::int32_t>(2));
        return -ceil_div;
    }
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints((static_cast<std::int32_t>(10) + modifier(constitution))) {
}

}  // namespace dnd_character
