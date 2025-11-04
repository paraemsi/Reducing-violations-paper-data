#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount
{
public:
    Bankaccount() noexcept;

    // Open the account – balance is reset to 0
    void open();

    // Close the account – further operations will fail
    void close();

    // Deposit (positive) or withdraw (negative) an amount.
    // Throws std::runtime_error if the account is closed or the
    // operation would overdraw the balance.
    void deposit(std::int64_t amount);

    // Withdraw the specified positive amount.
    void withdraw(std::int64_t amount);

    // Current balance; throws if the account is closed
    [[nodiscard]] std::int64_t balance() const;

private:
    mutable std::mutex m_mutex;
    bool m_is_open;
    std::int64_t m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
