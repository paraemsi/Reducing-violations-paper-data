#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept = default;

void Bankaccount::open()
{
    std::lock_guard<std::mutex> const lock(m_mutex);
    if (m_open) {
        throw std::runtime_error("account already open");
    }
    m_balance = static_cast<Amount>(0); /* reset balance                  */
    m_open    = true;
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> const lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account not open");
    }
    m_open = false;
}

void Bankaccount::deposit(Amount const amount)
{
    if (amount < static_cast<Amount>(0)) {
        throw std::runtime_error("negative deposit not allowed");
    }

    std::lock_guard<std::mutex> const lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account is closed");
    }

    m_balance += amount;
}

void Bankaccount::withdraw(Amount const amount)
{
    if (amount < static_cast<Amount>(0)) {
        throw std::runtime_error("negative withdrawal not allowed");
    }

    std::lock_guard<std::mutex> const lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account is closed");
    }

    if (m_balance < amount) {
        throw std::runtime_error("insufficient funds");
    }

    m_balance -= amount;
}

Amount Bankaccount::balance() const
{
    std::lock_guard<std::mutex> const lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account is closed");
    }
    return m_balance;
}

bool Bankaccount::is_open() const noexcept
{
    std::lock_guard<std::mutex> const lock(m_mutex);
    return m_open;
}

}  /* namespace Bankaccount */
