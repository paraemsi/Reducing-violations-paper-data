#include "bank_account.h"

#include <limits>
#include <stdexcept>
#include <mutex>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_is_open(false), m_balance(static_cast<Bankaccount::amount_type>(0)) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_is_open) {
        throw std::runtime_error("Account already open");
    } else {
        m_balance = static_cast<Bankaccount::amount_type>(0);
        m_is_open = true;
    }
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account already closed");
    } else {
        m_is_open = false;
        m_balance = static_cast<Bankaccount::amount_type>(0);
    }
}

void Bankaccount::deposit(Bankaccount::amount_type amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    } else {
        if (amount < static_cast<Bankaccount::amount_type>(0)) {
            throw std::runtime_error("Deposit amount must be non-negative");
        } else {
            const Bankaccount::amount_type max_val = (std::numeric_limits<Bankaccount::amount_type>::max)();
            if (amount > (max_val - m_balance)) {
                throw std::overflow_error("Deposit would overflow balance");
            } else {
                m_balance = (m_balance + amount);
            }
        }
    }
}

void Bankaccount::withdraw(Bankaccount::amount_type amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    } else {
        if (amount < static_cast<Bankaccount::amount_type>(0)) {
            throw std::runtime_error("Withdrawal amount must be non-negative");
        } else {
            if (amount > m_balance) {
                throw std::runtime_error("Insufficient funds");
            } else {
                m_balance = (m_balance - amount);
            }
        }
    }
}

Bankaccount::amount_type Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    } else {
        return m_balance;
    }
}

}  // namespace Bankaccount
