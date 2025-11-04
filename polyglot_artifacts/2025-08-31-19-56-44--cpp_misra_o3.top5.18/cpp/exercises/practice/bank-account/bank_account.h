#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

/*
 * Thread-safe bank account supporting open / close,
 * deposits, withdrawals and balance inquiry.
 */
class Bankaccount final {
public:
    Bankaccount() noexcept;

    /* open() initialises the account with zero balance.
     * Throws std::logic_error if the account is already open.
     */
    void open();

    /* close() resets balance to zero and marks account closed.
     * Throws std::logic_error if the account is already closed.
     */
    void close();

    /* deposit() adds a non-negative amount to the balance.
     * Throws std::invalid_argument for negative amount.
     * Throws std::logic_error     if account is closed.
     */
    void deposit(std::int32_t amount);

    /* withdraw() subtracts a non-negative amount from the balance.
     * Throws std::invalid_argument for negative amount.
     * Throws std::logic_error     if account is closed or funds insufficient.
     */
    void withdraw(std::int32_t amount);

    /* balance() returns current balance.
     * Throws std::logic_error if account is closed.
     */
    std::int32_t balance() const;

private:
    mutable std::mutex m_mutex{};
    bool               m_open{false};
    std::int32_t       m_balance{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
