#include "bank_account.h"

#include <limits>
#include <stdexcept>
#include <mutex>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex()
    , m_is_open(false)
    , m_balance(static_cast<Amount>(0))
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_is_open)) {
        throw std::runtime_error("Account already open");
    } else {
        m_is_open = true;
        m_balance = static_cast<Amount>(0);
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((!m_is_open)) {
        throw std::runtime_error("Account already closed");
    } else {
        m_is_open = false;
    }
}

void Bankaccount::deposit(Amount amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((!m_is_open)) {
        throw std::runtime_error("Account is closed");
    } else if ((amount < static_cast<Amount>(0))) {
        throw std::runtime_error("Negative deposit");
    } else if ((amount > static_cast<Amount>(0)) &&
               (m_balance > (std::numeric_limits<Amount>::max() - amount))) {
        throw std::runtime_error("Deposit overflow");
    } else {
        m_balance = m_balance + amount;
    }
}

void Bankaccount::withdraw(Amount amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((!m_is_open)) {
        throw std::runtime_error("Account is closed");
    } else if ((amount < static_cast<Amount>(0))) {
        throw std::runtime_error("Negative withdrawal");
    } else if ((amount > m_balance)) {
        throw std::runtime_error("Insufficient funds");
    } else {
        m_balance = m_balance - amount;
    }
}

Amount Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((!m_is_open)) {
        throw std::runtime_error("Account is closed");
    } else {
        return m_balance;
    }
}

}  // namespace Bankaccount
