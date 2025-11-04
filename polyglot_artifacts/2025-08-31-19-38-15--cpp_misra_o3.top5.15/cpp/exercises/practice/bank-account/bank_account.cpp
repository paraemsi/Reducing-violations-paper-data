#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {


Bankaccount::Bankaccount() noexcept :
    m_open(false),
    m_balance(static_cast<std::int64_t>(0)) {}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_open) {
        throw std::runtime_error("Account already open");
    } else {
        m_open   = true;
        m_balance = static_cast<std::int64_t>(0);
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_open) {
        throw std::runtime_error("Account already closed");
    } else {
        m_open   = false;
        m_balance = static_cast<std::int64_t>(0);
    }
}

void Bankaccount::deposit(std::int64_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_open) {
        throw std::runtime_error("Cannot deposit to a closed account");
    }
    if (amount <= static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Deposit amount must be positive");
    }

    m_balance += amount;
}

void Bankaccount::withdraw(std::int64_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_open) {
        throw std::runtime_error("Cannot withdraw from a closed account");
    }
    if (amount <= static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    if (m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    }

    m_balance -= amount;
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_open) {
        throw std::runtime_error("Cannot get balance of a closed account");
    }

    return m_balance;
}

}  // namespace Bankaccount

