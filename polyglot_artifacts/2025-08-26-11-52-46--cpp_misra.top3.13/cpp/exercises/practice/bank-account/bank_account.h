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
    // Throws std::runtime_error if account is closed
    money_t balance() const;

private:
    money_t m_balance;
    bool m_open;
    mutable std::mutex m_mutex;
public:
    // Deprecated: for backward compatibility, but not used by tests
    bool get_balance(money_t& out_balance);
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
