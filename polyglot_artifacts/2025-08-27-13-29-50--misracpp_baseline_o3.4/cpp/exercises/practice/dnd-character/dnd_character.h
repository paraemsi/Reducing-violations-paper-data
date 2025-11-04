#pragma once

namespace dnd_character {

int ability();                // roll 4d6 and drop the lowest
int modifier(int score);      // floor((score - 10) / 2)

class Character {
public:
    Character();

    int strength{};
    int dexterity{};
    int constitution{};
    int intelligence{};
    int wisdom{};
    int charisma{};
    int hitpoints{};          // 10 + constitution modifier
};

}  // namespace dnd_character
