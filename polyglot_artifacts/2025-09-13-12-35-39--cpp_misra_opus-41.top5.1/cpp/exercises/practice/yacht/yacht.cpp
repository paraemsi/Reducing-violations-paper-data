#include "yacht.h"
#include <algorithm>
#include <unordered_map>

namespace yacht {

// Helper function to count occurrences of each die value
static std::unordered_map<std::uint8_t, std::uint8_t> count_dice(const std::vector<std::uint8_t>& dice) {
    std::unordered_map<std::uint8_t, std::uint8_t> counts;
    for (const auto& die : dice) {
        std::uint8_t current_count = counts[die];
        counts[die] = static_cast<std::uint8_t>(current_count + 1U);
    }
    return counts;
}

// Helper function to calculate sum of all dice
static std::uint32_t sum_all_dice(const std::vector<std::uint8_t>& dice) {
    std::uint32_t sum = 0U;
    for (const auto& die : dice) {
        sum = sum + static_cast<std::uint32_t>(die);
    }
    return sum;
}

// Helper function to calculate sum of dice with specific value
static std::uint32_t sum_specific_value(const std::vector<std::uint8_t>& dice, std::uint8_t value) {
    std::uint32_t sum = 0U;
    for (const auto& die : dice) {
        if (die == value) {
            sum = sum + static_cast<std::uint32_t>(value);
        }
    }
    return sum;
}

// Helper function to check if dice form a full house
static bool is_full_house(const std::unordered_map<std::uint8_t, std::uint8_t>& counts) {
    bool has_three = false;
    bool has_two = false;
    
    for (const auto& pair : counts) {
        if (pair.second == 3U) {
            has_three = true;
        } else if (pair.second == 2U) {
            has_two = true;
        }
    }
    
    return (has_three && has_two);
}

// Helper function to find four of a kind value
static std::uint8_t find_four_of_kind_value(const std::unordered_map<std::uint8_t, std::uint8_t>& counts) {
    for (const auto& pair : counts) {
        if (pair.second >= 4U) {
            return pair.first;
        }
    }
    return 0U;
}

// Helper function to check if all dice are the same (yacht)
static bool is_yacht(const std::unordered_map<std::uint8_t, std::uint8_t>& counts) {
    return (counts.size() == 1U) && (counts.begin()->second == 5U);
}

// Helper function to check for little straight (1-2-3-4-5)
static bool is_little_straight(const std::vector<std::uint8_t>& dice) {
    std::vector<std::uint8_t> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
    if (sorted_dice.size() != 5U) {
        return false;
    }
    
    return (sorted_dice[0] == 1U) && 
           (sorted_dice[1] == 2U) && 
           (sorted_dice[2] == 3U) && 
           (sorted_dice[3] == 4U) && 
           (sorted_dice[4] == 5U);
}

// Helper function to check for big straight (2-3-4-5-6)
static bool is_big_straight(const std::vector<std::uint8_t>& dice) {
    std::vector<std::uint8_t> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
    if (sorted_dice.size() != 5U) {
        return false;
    }
    
    return (sorted_dice[0] == 2U) && 
           (sorted_dice[1] == 3U) && 
           (sorted_dice[2] == 4U) && 
           (sorted_dice[3] == 5U) && 
           (sorted_dice[4] == 6U);
}

std::uint32_t score(std::vector<std::uint8_t> dice, const std::string& category) {
    auto counts = count_dice(dice);
    
    if (category == "ones") {
        return sum_specific_value(dice, 1U);
    } else if (category == "twos") {
        return sum_specific_value(dice, 2U);
    } else if (category == "threes") {
        return sum_specific_value(dice, 3U);
    } else if (category == "fours") {
        return sum_specific_value(dice, 4U);
    } else if (category == "fives") {
        return sum_specific_value(dice, 5U);
    } else if (category == "sixes") {
        return sum_specific_value(dice, 6U);
    } else if (category == "full house") {
        if (is_full_house(counts)) {
            return sum_all_dice(dice);
        }
        return 0U;
    } else if (category == "four of a kind") {
        std::uint8_t four_kind_value = find_four_of_kind_value(counts);
        if (four_kind_value != 0U) {
            return static_cast<std::uint32_t>(four_kind_value) * 4U;
        }
        return 0U;
    } else if (category == "little straight") {
        if (is_little_straight(dice)) {
            return 30U;
        }
        return 0U;
    } else if (category == "big straight") {
        if (is_big_straight(dice)) {
            return 30U;
        }
        return 0U;
    } else if (category == "choice") {
        return sum_all_dice(dice);
    } else if (category == "yacht") {
        if (is_yacht(counts)) {
            return 50U;
        }
        return 0U;
    }
    
    return 0U;
}

}  // namespace yacht
