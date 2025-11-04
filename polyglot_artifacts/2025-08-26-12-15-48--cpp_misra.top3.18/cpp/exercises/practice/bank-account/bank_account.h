#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

using money_t = std::int64_t;

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();

    // Open the account (if not already open)
    void open();

    // Close the account (no further operations allowed)
    void close();

    // Deposit money into the account
    // Returns true on success, false if account is closed or amount is invalid
    bool deposit(money_t amount);

    // Withdraw money from the account
    // Returns true on success, false if insufficient funds or account is closed or amount is invalid
    bool withdraw(money_t amount);

    // Get the current balance
    // Returns false if account is closed, true and sets out_balance otherwise
    bool get_balance(money_t& out_balance);

    // Returns the current balance, throws std::runtime_error if account is closed
    money_t balance();

private:
    money_t m_balance;
    bool m_open;
    // mutex must not be mutable per MISRA C++:2008 Rule 7-1-1
    // NOLINTNEXTLINE(cppcoreguidelines-non-private-member-variables-in-classes)
    std::mutex m_mutex;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
