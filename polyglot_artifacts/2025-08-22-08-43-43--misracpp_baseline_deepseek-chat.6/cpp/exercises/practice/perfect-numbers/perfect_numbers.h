#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

namespace perfect_numbers {

enum classification {
    perfect,
    abundant,
    deficient
};

classification classify(int num);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
