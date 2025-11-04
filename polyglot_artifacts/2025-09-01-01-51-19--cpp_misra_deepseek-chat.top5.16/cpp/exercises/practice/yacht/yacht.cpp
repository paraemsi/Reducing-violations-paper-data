#include "yacht.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <cstdint>

namespace yacht {

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category) {
    if (dice.size() != 5) {
        return 0;
    }
    
    // Make a sorted copy to work with
    std::vector<std::int32_t> sorted_dice = dice;
    std::sort(sorted_dice.begin(), sorted_dice.end());
    
    if (category == "ones") {
        std::int32_t count = 0;
        for (std::int32_t num : dice) {
            if (num == 1) {
                count++;
            }
        }
        return 1 * count;
    } else { 
        if (category == "twos") {
            std::int32_t count = 0;
            for (std::int32_t num : dice) {
                if (num == 2) {
                    count++;
                }
            }
            return 2 * count;
        } else { 
            if (category == "threes") {
                std::int32_t count = 0;
                for (std::int32_t num : dice) {
                    if (num == 3) {
                        count++;
                    }
                }
                return 3 * count;
            } else { 
                if (category == "fours") {
                    std::int32_t count = 0;
                    for (std::int32_t num : dice) {
                        if (num == 4) {
                            count++;
                        }
                    }
                    return 4 * count;
                } else { 
                    if (category == "fives") {
                        std::int32_t count = 0;
                        for (std::int32_t num : dice) {
                            if (num == 5) {
                                count++;
                            }
                        }
                        return 5 * count;
                    } else { 
                        if (category == "sixes") {
                            std::int32_t count = 0;
                            for (std::int32_t num : dice) {
                                if (num == 6) {
                                    count++;
                                }
                            }
                            return 6 * count;
                        } else { 
                            if (category == "full house") {
                                // Check if there are exactly two distinct numbers with counts 3 and 2
                                std::map<std::int32_t, std::int32_t> counts;
                                for (std::int32_t num : dice) {
                                    counts[num]++;
                                }
                                if (counts.size() == 2) {
                                    auto it = counts.begin();
                                    std::int32_t first_count = it->second;
                                    it++;
                                    std::int32_t second_count = it->second;
                                    if ((((first_count == 2) && (second_count == 3)) || 
                                        ((first_count == 3) && (second_count == 2)))) {
                                        std::int32_t total = 0;
                                        for (std::int32_t num : dice) {
                                            total += num;
                                        }
                                        return total;
                                    }
                                }
                                return 0;
                            } else { 
                                if (category == "four of a kind") {
                                    std::map<std::int32_t, std::int32_t> counts;
                                    for (std::int32_t num : dice) {
                                        counts[num]++;
                                    }
                                    for (const auto& pair : counts) {
                                        if (pair.second >= 4) {
                                            return 4 * pair.first;
                                        }
                                    }
                                    return 0;
                                } else { 
                                    if (category == "little straight") {
                                        // Check if dice are 1-5
                                        std::vector<std::int32_t> expected = {1, 2, 3, 4, 5};
                                        if (sorted_dice == expected) {
                                            return 30;
                                        }
                                        return 0;
                                    } else { 
                                        if (category == "big straight") {
                                            // Check if dice are 2-6
                                            std::vector<std::int32_t> expected = {2, 3, 4, 5, 6};
                                            if (sorted_dice == expected) {
                                                return 30;
                                            }
                                            return 0;
                                        } else { 
                                            if (category == "choice") {
                                                std::int32_t total = 0;
                                                for (std::int32_t num : dice) {
                                                    total += num;
                                                }
                                                return total;
                                            } else { 
                                                if (category == "yacht") {
                                                    // All dice are the same
                                                    bool all_same = true;
                                                    for (std::int32_t i = 1; i < 5; i++) {
                                                        if (dice[i] != dice[0]) {
                                                            all_same = false;
                                                            break;
                                                        }
                                                    }
                                                    if (all_same) {
                                                        return 50;
                                                    }
                                                    return 0;
                                                } else {
                                                    return 0;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

}  // namespace yacht
