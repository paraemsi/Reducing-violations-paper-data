#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <optional>

namespace Bankaccount {

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();

    // Open the account (reset balance to 0, mark as open)
    void open();

    // Close the account (no further operations allowed)
    void close();

    // Get the current balance (throws if closed)
    int balance();

    // Deposit money (throws if closed or amount < 0)
    void deposit(int amount);

    // Withdraw money (throws if closed or insufficient funds or amount < 0)
    void withdraw(int amount);

private:
    int m_balance;
    bool m_open;
    mutable std::mutex m_mutex;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
