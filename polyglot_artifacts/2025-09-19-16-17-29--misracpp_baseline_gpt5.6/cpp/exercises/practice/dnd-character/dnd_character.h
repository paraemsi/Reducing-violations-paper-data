#pragma once

namespace dnd_character {

int ability();
int modifier(int score);

class Character {
public:
    Character();

    int strength{};
    int dexterity{};
    int constitution{};
    int intelligence{};
    int wisdom{};
    int charisma{};
    int hitpoints{};
};

}  // namespace dnd_character
