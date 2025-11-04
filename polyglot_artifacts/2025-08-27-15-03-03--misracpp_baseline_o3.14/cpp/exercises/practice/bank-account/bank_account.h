#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {
public:
    // Opens the account. Throws std::logic_error if already open.
    void open();

    // Closes the account. Throws std::logic_error if already closed.
    void close();

    // Deposits a positive amount into the account.
    // Throws std::logic_error if the account is closed
    // or if amount is negative.
    void deposit(int amount);

    // Withdraws a positive amount from the account.
    // Throws std::logic_error if the account is closed,
    // if amount is negative, or if amount exceeds the balance.
    void withdraw(int amount);

    // Returns the current account balance.
    // Throws std::logic_error if the account is closed.
    int balance() const;

private:
    bool is_open_{false};
    int balance_{0};
    mutable std::mutex mutex_;
};  // class bank_account

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
