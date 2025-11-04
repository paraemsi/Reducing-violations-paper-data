#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

/* MISRA: Use a type alias for money_t instead of typedef */
typedef std::int64_t money_t;

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

    // Provide a public balance() accessor for tests
    money_t balance();

private:
    money_t m_balance;
    bool m_open;
    std::mutex m_mutex;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
