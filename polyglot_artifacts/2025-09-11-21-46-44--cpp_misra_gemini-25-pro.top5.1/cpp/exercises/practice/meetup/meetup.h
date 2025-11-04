#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

class scheduler {
   public:
    enum class week { first, second, third, fourth, last, teenth };

    scheduler(boost::gregorian::greg_month month,
              boost::gregorian::greg_year year);

    boost::gregorian::date day(boost::gregorian::greg_weekday weekday,
                               week schedule) const;

   private:
    boost::gregorian::greg_month month_;
    boost::gregorian::greg_year year_;
};

}  // namespace meetup

#endif  // MEETUP_H
