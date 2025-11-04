#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H
#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {
class Bankaccount {
public:
    Bankaccount();

    // Open the account. Initializes balance to 0.
    // Throws std::runtime_error if the account is already open.
    void open();

    // Close the account. After closing, any operation except open()
    // will throw std::runtime_error.
    // Throws std::runtime_error if the account is already closed.
    void close();

    // Return current balance.
    // Throws std::runtime_error if the account is closed.
    int64_t balance() const;

    // Deposit amount (> 0) to the account.
    // Throws std::runtime_error if amount is negative or account is closed.
    void deposit(int64_t amount);

    // Withdraw amount (> 0) from the account.
    // Throws std::runtime_error if insufficient funds, amount is negative,
    // or the account is closed.
    void withdraw(int64_t amount);

private:
    mutable std::mutex m_mutex{};
    bool m_open{false};
    int64_t m_balance{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
