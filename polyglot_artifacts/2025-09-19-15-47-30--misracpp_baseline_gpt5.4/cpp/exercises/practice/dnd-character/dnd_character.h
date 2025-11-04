#pragma once

namespace dnd_character {

// Roll four 6-sided dice, drop the lowest, and sum the remaining three.
int ability();

// Compute the ability modifier: floor((score - 10) / 2).
int modifier(int score);

 // Randomly generated DnD character.
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
          hitpoints(0) {
        hitpoints = 10 + modifier(constitution);
    }
};

}  // namespace dnd_character
