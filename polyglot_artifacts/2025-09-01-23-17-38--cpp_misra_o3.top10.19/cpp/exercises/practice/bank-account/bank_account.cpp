#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() = default;

void Bankaccount::open()
{
    std::lock_guard<std::mutex> const lock {m_mutex};

    if (m_isOpen) {
        throw std::runtime_error("Account already open");
    } else {
        m_isOpen  = true;
        m_balance = static_cast<Money>(0);
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> const lock {m_mutex};

    if (!m_isOpen) {
        throw std::runtime_error("Account already closed");
    } else {
        m_isOpen = false;
    }
}

Money Bankaccount::balance() const
{
    std::lock_guard<std::mutex> const lock {m_mutex};

    if (!m_isOpen) {
        throw std::runtime_error("Account is closed");
    }

    return m_balance;
}

void Bankaccount::deposit(Money const amount)
{
    if (amount <= static_cast<Money>(0)) {
        throw std::invalid_argument("Deposit must be positive");
    }

    std::lock_guard<std::mutex> const lock {m_mutex};

    if (!m_isOpen) {
        throw std::runtime_error("Account is closed");
    }

    m_balance += amount;
}

void Bankaccount::withdraw(Money const amount)
{
    if (amount <= static_cast<Money>(0)) {
        throw std::invalid_argument("Withdrawal must be positive");
    }

    std::lock_guard<std::mutex> const lock {m_mutex};

    if (!m_isOpen) {
        throw std::runtime_error("Account is closed");
    }

    if (m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    }

    m_balance -= amount;
}

}  // namespace Bankaccount
