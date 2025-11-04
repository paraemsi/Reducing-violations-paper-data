#include "bank_account.h"

#include <mutex>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex(),
      m_is_open(false),
      m_balance(0)
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_is_open) {
        throw std::runtime_error("account already open");
    }
    m_balance = 0;
    m_is_open = true;
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("account not open");
    }
    m_is_open = false;
    m_balance = 0;
}

void Bankaccount::deposit(std::int64_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("cannot deposit negative amount");
    }
    m_balance = (m_balance + amount);
}

void Bankaccount::withdraw(std::int64_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("cannot withdraw negative amount");
    }
    if (m_balance < amount) {
        throw std::runtime_error("insufficient funds");
    }
    m_balance = (m_balance - amount);
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("account is closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
