#include "zebra_puzzle.h"
#include <algorithm>

namespace zebra_puzzle {

namespace {

using std::string;
using std::array;
using std::vector;

// Type aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using house_t = array<index_t, 5U>;
using perm_t = array<index_t, 5U>;

// All possible values for each attribute
constexpr array<const char*, 5U> COLORS = {"red", "green", "ivory", "yellow", "blue"};
constexpr array<const char*, 5U> NATIONALITIES = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
constexpr array<const char*, 5U> PETS = {"dog", "snails", "fox", "horse", "zebra"};
constexpr array<const char*, 5U> DRINKS = {"coffee", "tea", "milk", "orange juice", "water"};
constexpr array<const char*, 5U> HOBBIES = {"dancing", "painter", "reading", "football", "chess"};

// Helper to check if two houses are neighbors
inline bool is_neighbor(index_t a, index_t b)
{
    return (a == (b + 1U)) || (b == (a + 1U));
}

// Helper to generate all permutations of 0..4
vector<perm_t> all_permutations()
{
    perm_t p = {0U, 1U, 2U, 3U, 4U};
    vector<perm_t> perms;
    do {
        perms.push_back(p);
    } while (std::next_permutation(p.begin(), p.end()));
    return perms;
}

} // anonymous namespace

Solution solve()
{
    // Generate all permutations for each attribute
    const vector<perm_t> perms = all_permutations();

    // For each possible arrangement of nationalities
    for(const perm_t& nat : perms) {
        // 10. The Norwegian lives in the first house.
        if(nat[3U] != 0U) { continue; } // Norwegian must be in house 0

        // 2. The Englishman lives in the red house.
        for(const perm_t& col : perms) {
            if(nat[0U] != col[0U]) { continue; } // Englishman <-> red

            // 15. The Norwegian lives next to the blue house.
            if(!is_neighbor(nat[3U], col[4U])) { continue; } // Norwegian <-> blue

            // 6. The green house is immediately to the right of the ivory house.
            if((col[1U] != (col[2U] + 1U))) { continue; } // green is right of ivory

            // 4. The person in the green house drinks coffee.
            for(const perm_t& dri : perms) {
                if(col[1U] != dri[0U]) { continue; } // green <-> coffee

                // 9. The person in the middle house drinks milk.
                if(dri[2U] != 2U) { continue; } // milk in house 2

                // 5. The Ukrainian drinks tea.
                if(nat[2U] != dri[1U]) { continue; } // Ukrainian <-> tea

                // 13. The person who plays football drinks orange juice.
                for(const perm_t& hob : perms) {
                    if(hob[3U] != dri[3U]) { continue; } // football <-> orange juice

                    // 14. The Japanese person plays chess.
                    if(nat[4U] != hob[4U]) { continue; } // Japanese <-> chess

                    // 8. The person in the yellow house is a painter.
                    if(col[3U] != hob[1U]) { continue; } // yellow <-> painter

                    // 7. The snail owner likes to go dancing.
                    for(const perm_t& pet : perms) {
                        if(pet[1U] != hob[0U]) { continue; } // snails <-> dancing

                        // 3. The Spaniard owns the dog.
                        if(nat[1U] != pet[0U]) { continue; } // Spaniard <-> dog

                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        if(!is_neighbor(hob[2U], pet[2U])) { continue; } // reading <-> fox

                        // 12. The painter's house is next to the house with the horse.
                        if(!is_neighbor(hob[1U], pet[3U])) { continue; } // painter <-> horse

                        // All constraints satisfied, extract solution
                        index_t water_idx = 0U;
                        index_t zebra_idx = 0U;
                        for(index_t i = 0U; i < 5U; ++i) {
                            if(dri[i] == 4U) { water_idx = i; }
                            if(pet[i] == 4U) { zebra_idx = i; }
                        }
                        Solution sol;
                        sol.drinksWater = NATIONALITIES[water_idx];
                        sol.ownsZebra = NATIONALITIES[zebra_idx];
                        return sol;
                    }
                }
            }
        }
    }
    // If no solution found, return empty
    Solution sol;
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle
