#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <stdexcept>

namespace Bankaccount {

class Bankaccount {
public:
    // open the account; resets balance to 0
    void open();

    // close the account; further operations will throw
    void close();

    // add money to the account (amount must be non-negative)
    void deposit(int amount);

    // withdraw money from the account (must have sufficient funds)
    void withdraw(int amount);

    // current balance
    int balance() const;

    // Disable copy and move – a bank account represents a single resource
    Bankaccount(const Bankaccount&)            = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    Bankaccount(Bankaccount&&)                 = delete;
    Bankaccount& operator=(Bankaccount&&)      = delete;

private:
    mutable std::mutex m_;
    bool open_{false};
    int balance_{0};
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
