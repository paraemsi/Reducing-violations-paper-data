#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

/*
 *  A simple thread-safe bank account.
 *  All monetary values are represented with std::int64_t to follow
 *  MISRA-C++ fixed-width integer recommendations.
 */
class Bankaccount
{
public:
    Bankaccount();

    /* Open the account – sets balance to 0.
     * Calling open() on an already-open account throws.
     */
    void open();

    /* Close the account – further operations will throw.
     * It is undefined behaviour to close an account that is already closed.
     */
    void close();

    /* Return current balance.
     * Throws if the account is closed.
     */
    [[nodiscard]] std::int64_t balance() const;

    /* Deposit a strictly positive amount.
     * Throws if amount <= 0 or account is closed.
     */
    void deposit(std::int64_t amount);

    /* Withdraw a strictly positive amount not exceeding the balance.
     * Throws if amount <= 0, insufficient funds, or account is closed.
     */
    void withdraw(std::int64_t amount);

private:
    mutable std::mutex m_mutex;
    bool m_open;
    std::int64_t m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
