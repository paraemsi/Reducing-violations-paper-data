#include "dnd_character.h"

#include <algorithm>
#include <cstdint>
#include <random>

namespace {

// Thread-local PRNG to avoid re-seeding on every roll.
auto rng() -> std::mt19937& {
    static thread_local std::mt19937 gen{std::random_device{}()};
    return gen;
}

auto roll_d6() -> std::int32_t {
    static thread_local std::uniform_int_distribution<std::int32_t> dist{1, 6};
    return dist(rng());
}

}  // unnamed namespace

namespace dnd_character {


auto ability() -> std::int32_t {
    const std::int32_t r1 = roll_d6();
    const std::int32_t r2 = roll_d6();
    const std::int32_t r3 = roll_d6();
    const std::int32_t r4 = roll_d6();

    const std::int32_t smallest_pair1 = (std::min)(r1, r2);
    const std::int32_t smallest_pair2 = (std::min)(r3, r4);
    const std::int32_t smallest = (std::min)(smallest_pair1, smallest_pair2);

    const std::int32_t total = ((r1 + r2) + r3) + r4;
    return (total - smallest);
}

Character::Character() {
    strength = ability();
    dexterity = ability();
    constitution = ability();
    intelligence = ability();
    wisdom = ability();
    charisma = ability();

    const std::int32_t base_hp = 10;
    hitpoints = (base_hp + modifier(constitution));
}


}  // namespace dnd_character
