#include "gigasecond.h"

namespace gigasecond {

auto advance(const ptime& tp) -> ptime
{
    return (tp + gigasecond);
}

}  // namespace gigasecond
