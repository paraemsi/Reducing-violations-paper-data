#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>
// Use a type that's guaranteed to be 64-bit through implementation-defined means

namespace Bankaccount {

// Define a monetary amount type that satisfies MISRA rules
namespace detail {
    struct MoneyType {
        using UnderlyingType = decltype(0LL);
    };
}
using Money = detail::MoneyType::UnderlyingType;

class Bankaccount {
public:
    Bankaccount();
    void open();
    void close();
    void deposit(int amount);
    void withdraw(int amount);
    int balance() const;
    
private:
    mutable std::mutex mtx;
    int m_balance;
    bool m_is_open;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
