#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

/*
 * MISRA: Use a typedef/using alias to a fixed-width type, but do not use the standard type name directly elsewhere.
 * The following alias is permitted by MISRA as long as std::int64_t is not used elsewhere.
 */
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
    bool get_balance(money_t & out_balance);

    // Provide a public balance() method for test compatibility
    money_t balance();

private:
    money_t m_balance;
    bool m_open;
    /*
     * MISRA: std::mutex is not copyable, so mutable is not strictly needed, but allowed for const methods.
     * The mutex is used to synchronize access to the account for thread safety.
     */
    mutable std::mutex m_mutex;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
