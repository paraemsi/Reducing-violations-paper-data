#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() :
    m_mutex(),
    m_is_open(false),
    m_balance(static_cast<std::int64_t>(0))
{
    /* Constructor body intentionally left empty */
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_is_open) {
        throw std::runtime_error("Account already open");
    }
    m_is_open = true;
    m_balance = static_cast<std::int64_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account already closed");
    }
    m_is_open = false;
}

void Bankaccount::deposit(std::int64_t amount)
{
    if (amount < static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Deposit amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Cannot deposit to a closed account");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(std::int64_t amount)
{
    if (amount < static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Withdrawal amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Cannot withdraw from a closed account");
    }
    if (m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
