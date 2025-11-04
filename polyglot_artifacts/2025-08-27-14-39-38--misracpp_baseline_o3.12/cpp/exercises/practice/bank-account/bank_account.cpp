#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept = default;

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_open) {
        throw std::runtime_error("account already open");
    }
    m_open = true;
    m_balance = 0;
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account already closed");
    }
    m_open = false;
}

int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account closed");
    }
    return m_balance;
}

void Bankaccount::deposit(int64_t amount)
{
    if (amount < 0) {
        throw std::runtime_error("amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account closed");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(int64_t amount)
{
    if (amount < 0) {
        throw std::runtime_error("amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account closed");
    }
    if (amount > m_balance) {
        throw std::runtime_error("insufficient funds");
    }
    m_balance -= amount;
}

} // namespace Bankaccount
