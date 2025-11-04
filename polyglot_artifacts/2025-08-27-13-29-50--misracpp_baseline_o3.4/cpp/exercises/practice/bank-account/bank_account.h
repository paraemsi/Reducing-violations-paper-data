#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <stdexcept>

namespace Bankaccount {
class Bankaccount {
public:
    // Defaulted constructor – allows aggregate initialization (`Bankaccount account{}`) explicitly.
    Bankaccount() = default;
    // Open the account. Throws if the account is already open.
    void open();

    // Close the account. Throws if the account is already closed.
    void close();

    // Deposit money into the account. Amount must be non-negative and the
    // account must be open.
    void deposit(int amount);

    // Withdraw money from the account. Amount must be non-negative, the
    // account must be open and have sufficient funds.
    void withdraw(int amount);

    // Return the current balance. Throws if the account is closed.
    int balance() const;

private:
    mutable std::mutex mtx_;
    bool is_open_{false};
    int balance_{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
