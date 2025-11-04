#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <vector>

namespace zebra_puzzle {

namespace {

constexpr int N = 5;

enum Color { Red, Green, Ivory, Yellow, Blue };
enum Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum Pet { Dog, Snails, Fox, Horse, Zebra };
enum Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum Hobby { Reading, Dancing, Painting, Football, Chess };

struct House {
    Color color;
    Nationality nationality;
    Pet pet;
    Drink drink;
    Hobby hobby;
};

template <typename T>
std::array<T, N> make_array(const std::vector<T>& v) {
    std::array<T, N> arr;
    std::copy(v.begin(), v.end(), arr.begin());
    return arr;
}

bool is_valid(const std::array<House, N>& houses) {
    // 2. The Englishman lives in the red house.
    for (int i = 0; i < N; ++i)
        if (houses[i].nationality == Englishman && houses[i].color != Red)
            return false;

    // 3. The Spaniard owns the dog.
    for (int i = 0; i < N; ++i)
        if (houses[i].nationality == Spaniard && houses[i].pet != Dog)
            return false;

    // 4. The person in the green house drinks coffee.
    for (int i = 0; i < N; ++i)
        if (houses[i].color == Green && houses[i].drink != Coffee)
            return false;

    // 5. The Ukrainian drinks tea.
    for (int i = 0; i < N; ++i)
        if (houses[i].nationality == Ukrainian && houses[i].drink != Tea)
            return false;

    // 6. The green house is immediately to the right of the ivory house.
    // (i.e., ivory is at i, green is at i+1)
    {
        bool found = false;
        for (int i = 0; i < N - 1; ++i)
            if (houses[i].color == Ivory && houses[i + 1].color == Green)
                found = true;
        if (!found)
            return false;
    }

    // 7. The snail owner likes to go dancing.
    for (int i = 0; i < N; ++i)
        if (houses[i].pet == Snails && houses[i].hobby != Dancing)
            return false;

    // 8. The person in the yellow house is a painter.
    for (int i = 0; i < N; ++i)
        if (houses[i].color == Yellow && houses[i].hobby != Painting)
            return false;

    // 9. The person in the middle house drinks milk.
    if (houses[2].drink != Milk)
        return false;

    // 10. The Norwegian lives in the first house.
    if (houses[0].nationality != Norwegian)
        return false;

    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    {
        bool found = false;
        for (int i = 0; i < N; ++i) {
            if (houses[i].hobby == Reading) {
                if ((i > 0 && houses[i - 1].pet == Fox) ||
                    (i < N - 1 && houses[i + 1].pet == Fox))
                    found = true;
            }
        }
        if (!found)
            return false;
    }

    // 12. The painter's house is next to the house with the horse.
    {
        bool found = false;
        for (int i = 0; i < N; ++i) {
            if (houses[i].hobby == Painting) {
                if ((i > 0 && houses[i - 1].pet == Horse) ||
                    (i < N - 1 && houses[i + 1].pet == Horse))
                    found = true;
            }
        }
        if (!found)
            return false;
    }

    // 13. The person who plays football drinks orange juice.
    for (int i = 0; i < N; ++i)
        if (houses[i].hobby == Football && houses[i].drink != OrangeJuice)
            return false;

    // 14. The Japanese person plays chess.
    for (int i = 0; i < N; ++i)
        if (houses[i].nationality == Japanese && houses[i].hobby != Chess)
            return false;

    // 15. The Norwegian lives next to the blue house.
    {
        bool found = false;
        for (int i = 0; i < N; ++i) {
            if (houses[i].nationality == Norwegian) {
                if ((i > 0 && houses[i - 1].color == Blue) ||
                    (i < N - 1 && houses[i + 1].color == Blue))
                    found = true;
            }
        }
        if (!found)
            return false;
    }

    return true;
}

std::string nationality_to_string(Nationality n) {
    switch (n) {
        case Englishman: return "Englishman";
        case Spaniard: return "Spaniard";
        case Ukrainian: return "Ukrainian";
        case Norwegian: return "Norwegian";
        case Japanese: return "Japanese";
    }
    return "";
}

} // namespace

Solution solve() {
    std::vector<Color> colors = {Red, Green, Ivory, Yellow, Blue};
    std::vector<Nationality> nationalities = {Englishman, Spaniard, Ukrainian, Norwegian, Japanese};
    std::vector<Pet> pets = {Dog, Snails, Fox, Horse, Zebra};
    std::vector<Drink> drinks = {Coffee, Tea, Milk, OrangeJuice, Water};
    std::vector<Hobby> hobbies = {Reading, Dancing, Painting, Football, Chess};

    // All permutations of each attribute
    std::array<int, N> idx = {0, 1, 2, 3, 4};

    // Norwegian must be in the first house, so fix that
    do {
        if (nationalities[idx[0]] != Norwegian)
            continue;
        std::array<Nationality, N> nat;
        for (int i = 0; i < N; ++i) nat[i] = nationalities[idx[i]];

        // For each color permutation, Norwegian must be next to blue
        std::array<int, N> cidx = {0, 1, 2, 3, 4};
        do {
            std::array<Color, N> col;
            for (int i = 0; i < N; ++i) col[i] = colors[cidx[i]];
            // Norwegian lives next to blue
            bool next_to_blue = (cidx[0] == 4 && cidx[1] == 1) || (cidx[0] == 1 && cidx[1] == 4) ||
                                (cidx[0] == 1 && cidx[1] == 4) || (cidx[1] == 1 && cidx[0] == 4);
            bool found = false;
            for (int i = 0; i < N; ++i) {
                if (nat[i] == Norwegian) {
                    if ((i > 0 && col[i - 1] == Blue) || (i < N - 1 && col[i + 1] == Blue))
                        found = true;
                }
            }
            if (!found)
                continue;

            // Green must be immediately right of ivory
            bool green_right_of_ivory = false;
            for (int i = 0; i < N - 1; ++i)
                if (col[i] == Ivory && col[i + 1] == Green)
                    green_right_of_ivory = true;
            if (!green_right_of_ivory)
                continue;

            // For each drink permutation, milk must be in the middle
            std::array<int, N> didx = {0, 1, 2, 3, 4};
            do {
                std::array<Drink, N> dr;
                for (int i = 0; i < N; ++i) dr[i] = drinks[didx[i]];
                if (dr[2] != Milk)
                    continue;

                // For each pet permutation
                std::array<int, N> pidx = {0, 1, 2, 3, 4};
                do {
                    std::array<Pet, N> pt;
                    for (int i = 0; i < N; ++i) pt[i] = pets[pidx[i]];

                    // For each hobby permutation
                    std::array<int, N> hidx = {0, 1, 2, 3, 4};
                    do {
                        std::array<Hobby, N> hb;
                        for (int i = 0; i < N; ++i) hb[i] = hobbies[hidx[i]];

                        std::array<House, N> houses;
                        for (int i = 0; i < N; ++i) {
                            houses[i] = House{col[i], nat[i], pt[i], dr[i], hb[i]};
                        }
                        if (is_valid(houses)) {
                            // Find who drinks water and who owns zebra
                            std::string drinksWater, ownsZebra;
                            for (int i = 0; i < N; ++i) {
                                if (houses[i].drink == Water)
                                    drinksWater = nationality_to_string(houses[i].nationality);
                                if (houses[i].pet == Zebra)
                                    ownsZebra = nationality_to_string(houses[i].nationality);
                            }
                            return Solution{drinksWater, ownsZebra};
                        }
                    } while (std::next_permutation(hidx.begin(), hidx.end()));
                } while (std::next_permutation(pidx.begin(), pidx.end()));
            } while (std::next_permutation(didx.begin(), didx.end()));
        } while (std::next_permutation(cidx.begin(), cidx.end()));
    } while (std::next_permutation(idx.begin(), idx.end()));

    return Solution{"", ""};
}

}  // namespace zebra_puzzle
