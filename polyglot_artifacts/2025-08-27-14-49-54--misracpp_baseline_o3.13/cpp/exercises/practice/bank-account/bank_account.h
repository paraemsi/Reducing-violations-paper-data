#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <stdexcept>

namespace Bankaccount {
class Bankaccount {
public:
    Bankaccount() noexcept;

    // Open the account. Throws if already open.
    void open();

    // Close the account. Throws if already closed.
    void close();

    // Return current balance. Throws if account is closed.
    int balance() const;

    // Add (or subtract) amount from balance.
    // Negative amounts perform a withdrawal.
    // Throws if account is closed or result would be negative.
    void deposit(int amount);
    // Withdraw amount from balance.
    // Throws if account is closed or insufficient funds.
    void withdraw(int amount);

private:
    mutable std::mutex m_;
    bool is_open_{false};
    int balance_{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
