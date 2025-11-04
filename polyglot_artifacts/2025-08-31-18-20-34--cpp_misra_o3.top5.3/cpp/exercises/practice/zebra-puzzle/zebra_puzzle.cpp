#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

//  Enumerations for every attribute in the puzzle -----------------------------

enum struct Color : std::uint8_t {
    Red,
    Green,
    Ivory,
    Yellow,
    Blue
};

enum struct Nationality : std::uint8_t {
    Englishman,
    Spaniard,
    Ukrainian,
    Norwegian,
    Japanese
};

enum struct Pet : std::uint8_t {
    Dog,
    Snails,
    Fox,
    Horse,
    Zebra
};

enum struct Drink : std::uint8_t {
    Coffee,
    Tea,
    Milk,
    OrangeJuice,
    Water
};

enum struct Hobby : std::uint8_t {
    Reading,
    Painting,
    Dancing,
    Football,
    Chess
};

//  Small utility that returns the index of value inside container -------------
template <typename T, std::size_t N>
static constexpr std::uint8_t index_of(const std::array<T, N>& cont,
                                       T                        value) noexcept
{
    for(std::uint8_t i {0U}; i < static_cast<std::uint8_t>(N); ++i) {
        if(cont[static_cast<std::size_t>(i)] == value) {
            return i;
        }
    }
    return static_cast<std::uint8_t>(255U);     //  Invalid – should never be reached for correct input
}

//  Solve the puzzle -----------------------------------------------------------
Solution solve()
{
    using std::array;
    using std::next_permutation;

    //  Canonical ordered sets for permutation generation
    array<Color, 5U>        colors       {Color::Red, Color::Green, Color::Ivory,
                                          Color::Yellow, Color::Blue};
    array<Nationality, 5U>  nations      {Nationality::Englishman, Nationality::Spaniard,
                                          Nationality::Ukrainian, Nationality::Norwegian,
                                          Nationality::Japanese};
    array<Pet, 5U>          pets         {Pet::Dog, Pet::Snails, Pet::Fox,
                                          Pet::Horse, Pet::Zebra};
    array<Drink, 5U>        drinks       {Drink::Coffee, Drink::Tea, Drink::Milk,
                                          Drink::OrangeJuice, Drink::Water};
    array<Hobby, 5U>        hobbies      {Hobby::Reading, Hobby::Painting, Hobby::Dancing,
                                          Hobby::Football, Hobby::Chess};

    //  Permute colours first – rule 6 can prune heavily
    do {
        const std::uint8_t green_idx {index_of(colors, Color::Green)};
        const std::uint8_t ivory_idx {index_of(colors, Color::Ivory)};

        if(green_idx != (ivory_idx + 1U)) {
            continue;   //  Rule 6: green house is immediately right of ivory
        }

        //  Nations next – several early constraints
        array<Nationality, 5U> nations_p {nations};
        do {
            const std::uint8_t red_idx        {index_of(colors, Color::Red)};
            if(nations_p[static_cast<std::size_t>(red_idx)] != Nationality::Englishman) {
                continue;   //  Rule 2
            }

            if(nations_p[0U] != Nationality::Norwegian) {
                continue;   //  Rule 10
            }

            const std::uint8_t blue_idx {index_of(colors, Color::Blue)};
            const std::uint8_t nor_idx  {0U};  //  from rule 10

            if(!((blue_idx == (nor_idx + 1U)) || ((blue_idx + 1U) == nor_idx))) {
                continue;   //  Rule 15
            }

            //  Drinks – more pruning available
            array<Drink, 5U> drinks_p {drinks};
            do {
                const std::uint8_t green_house {green_idx};
                if(drinks_p[static_cast<std::size_t>(green_house)] != Drink::Coffee) {
                    continue;   //  Rule 4
                }
                const std::uint8_t ukr_idx {index_of(nations_p, Nationality::Ukrainian)};
                if(drinks_p[static_cast<std::size_t>(ukr_idx)] != Drink::Tea) {
                    continue;   //  Rule 5
                }
                if(drinks_p[2U] != Drink::Milk) {
                    continue;   //  Rule 9 (middle house)
                }

                //  Hobbies – still before pets because of rule 12 and 13
                array<Hobby, 5U> hobbies_p {hobbies};
                do {
                    const std::uint8_t yellow_idx {index_of(colors, Color::Yellow)};
                    if(hobbies_p[static_cast<std::size_t>(yellow_idx)] != Hobby::Painting) {
                        continue;   //  Rule 8
                    }
                    const std::uint8_t jap_idx {index_of(nations_p, Nationality::Japanese)};
                    if(hobbies_p[static_cast<std::size_t>(jap_idx)] != Hobby::Chess) {
                        continue;   //  Rule 14
                    }

                    const std::uint8_t football_idx {index_of(hobbies_p, Hobby::Football)};
                    if(drinks_p[static_cast<std::size_t>(football_idx)] != Drink::OrangeJuice) {
                        continue;   //  Rule 13
                    }

                    const std::uint8_t dancing_idx {index_of(hobbies_p, Hobby::Dancing)};

                    //  Pets – last permutation set
                    array<Pet, 5U> pets_p {pets};
                    do {
                        const std::uint8_t span_idx {index_of(nations_p, Nationality::Spaniard)};
                        if(pets_p[static_cast<std::size_t>(span_idx)] != Pet::Dog) {
                            continue;   //  Rule 3
                        }

                        if(hobbies_p[static_cast<std::size_t>(dancing_idx)] != Hobby::Dancing) {
                            continue;   //  Defensive – already true
                        }
                        if(pets_p[static_cast<std::size_t>(dancing_idx)] != Pet::Snails) {
                            continue;   //  Rule 7
                        }

                        const std::uint8_t fox_idx {index_of(pets_p, Pet::Fox)};
                        const std::uint8_t reading_idx {index_of(hobbies_p, Hobby::Reading)};
                        if(!(((fox_idx + 1U) == reading_idx) || ((reading_idx + 1U) == fox_idx))) {
                            continue;   //  Rule 11
                        }

                        const std::uint8_t horse_idx {index_of(pets_p, Pet::Horse)};
                        const std::uint8_t painter_idx {index_of(hobbies_p, Hobby::Painting)};
                        if(!(((horse_idx + 1U) == painter_idx) || ((painter_idx + 1U) == horse_idx))) {
                            continue;   //  Rule 12
                        }

                        //  All constraints satisfied – compose answer
                        const std::uint8_t water_idx {index_of(drinks_p, Drink::Water)};
                        const std::uint8_t zebra_idx {index_of(pets_p,   Pet::Zebra)};

                        Solution result {};
                        result.drinksWater = [n = nations_p[static_cast<std::size_t>(water_idx)]]() {
                            switch(n) {
                                case Nationality::Englishman: return std::string("Englishman");
                                case Nationality::Spaniard:   return std::string("Spaniard");
                                case Nationality::Ukrainian:  return std::string("Ukrainian");
                                case Nationality::Norwegian:  return std::string("Norwegian");
                                case Nationality::Japanese:   return std::string("Japanese");
                                default:                      return std::string();
                            }
                        }();
                        result.ownsZebra = [n = nations_p[static_cast<std::size_t>(zebra_idx)]]() {
                            switch(n) {
                                case Nationality::Englishman: return std::string("Englishman");
                                case Nationality::Spaniard:   return std::string("Spaniard");
                                case Nationality::Ukrainian:  return std::string("Ukrainian");
                                case Nationality::Norwegian:  return std::string("Norwegian");
                                case Nationality::Japanese:   return std::string("Japanese");
                                default:                      return std::string();
                            }
                        }();
                        return result;

                    } while(next_permutation(pets_p.begin(), pets_p.end()));

                } while(next_permutation(hobbies_p.begin(), hobbies_p.end()));

            } while(next_permutation(drinks_p.begin(), drinks_p.end()));

        } while(next_permutation(nations_p.begin(), nations_p.end()));

    } while(next_permutation(colors.begin(), colors.end()));

    //  No solution found (should never happen for this puzzle)
    return Solution {};
}

}  // namespace zebra_puzzle
