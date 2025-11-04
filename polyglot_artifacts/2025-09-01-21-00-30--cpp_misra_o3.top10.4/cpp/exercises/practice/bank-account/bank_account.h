#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

// Alias used for all monetary values to comply with MISRA “no plain int”
using money_t = std::int64_t;

class Bankaccount {
public:
    Bankaccount() noexcept = default;

    // Open the account – sets balance to zero, throws if already open
    void open();

    // Close the account – throws if not open
    void close();

    // Thread-safe deposit – positive amounts only
    void deposit(money_t amount);

    // Thread-safe withdrawal – positive amounts only, throws if insufficient funds
    void withdraw(money_t amount);

    // Obtain current balance – valid only while account is open
    [[nodiscard]] money_t balance() const;

private:
    mutable std::mutex m_mutex {};     // protects all mutable state
    bool m_is_open {false};
    money_t m_balance {static_cast<money_t>(0)};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
