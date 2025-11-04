#pragma once

namespace dnd_character {

/**
 * Compute the ability modifier from an ability score.
 * The modifier is ⌊(score - 10) / 2⌋.
 */
int modifier(int score);

/**
 * Roll four six–sided dice, drop the lowest, and return the sum
 * of the remaining three dice.
 */
int ability();

/**
 * A randomly-generated Dungeons & Dragons character.
 */
class Character {
public:
    Character();

    // Public ability scores
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    /**
     * Hit points are 10 + constitution modifier.
     */
    int hitpoints;
};

}  // namespace dnd_character
