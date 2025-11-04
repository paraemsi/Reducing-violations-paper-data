#pragma once

namespace dnd_character {

// Compute the ability modifier from an ability score.
int modifier(int score);

// Roll four six-sided dice and sum the highest three.
int ability();

struct Character {
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
    int hitpoints;

    Character()
        : strength(ability()),
          dexterity(ability()),
          constitution(ability()),
          intelligence(ability()),
          wisdom(ability()),
          charisma(ability()),
          hitpoints(10 + modifier(constitution)) {}
};

}  // namespace dnd_character
