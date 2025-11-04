#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_open) {
        throw std::runtime_error("account already open");
    } else {
        m_open    = true;
        m_balance = static_cast<amount_t>(0);
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account already closed");
    } else {
        m_open = false;
    }
}

amount_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account not open");
    } else {
        return m_balance;
    }
}

void Bankaccount::deposit(amount_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account not open");
    } else {
        if (amount < static_cast<amount_t>(0)) {
            throw std::runtime_error("cannot deposit negative amount");
        } else {
            m_balance += amount;
        }
    }
}

void Bankaccount::withdraw(amount_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account not open");
    } else {
        if (amount < static_cast<amount_t>(0)) {
            throw std::runtime_error("cannot withdraw negative amount");
        } else {
            if (m_balance < amount) {
                throw std::runtime_error("insufficient funds");
            } else {
                m_balance -= amount;
            }
        }
    }
}

}  // namespace Bankaccount
