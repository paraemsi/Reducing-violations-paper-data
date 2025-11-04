#include "bank_account.h"

#include <mutex>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : m_mutex(), m_balance(static_cast<std::int64_t>(0)), m_is_open(false)
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_is_open == true)) {
        throw std::runtime_error("account already open");
    } else {
        m_is_open = true;
        m_balance = static_cast<std::int64_t>(0);
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_is_open == false)) {
        throw std::runtime_error("account already closed");
    } else {
        m_is_open = false;
    }
}

void Bankaccount::deposit(std::int64_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_is_open == false)) {
        throw std::runtime_error("account is closed");
    } else {
        if ((amount < static_cast<std::int64_t>(0))) {
            throw std::runtime_error("negative deposit");
        } else {
            m_balance = (m_balance + amount);
        }
    }
}

void Bankaccount::withdraw(std::int64_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_is_open == false)) {
        throw std::runtime_error("account is closed");
    } else {
        if ((amount < static_cast<std::int64_t>(0))) {
            throw std::runtime_error("negative withdrawal");
        } else {
            if ((amount > m_balance)) {
                throw std::runtime_error("insufficient funds");
            } else {
                m_balance = (m_balance - amount);
            }
        }
    }
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_is_open == false)) {
        throw std::runtime_error("account is closed");
    } else {
        return m_balance;
    }
}

}  // namespace Bankaccount
