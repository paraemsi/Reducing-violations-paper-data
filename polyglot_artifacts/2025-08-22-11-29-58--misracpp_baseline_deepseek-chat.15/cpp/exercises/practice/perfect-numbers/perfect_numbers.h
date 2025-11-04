#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

namespace perfect_numbers {

enum class classification {
    perfect = 0,
    abundant = 1,
    deficient = 2
};

classification classify(int num);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
