#include "bank_account.h"

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_is_open) {
        throw std::runtime_error("Account already open");
    } else {
        m_balance = static_cast<std::int64_t>(0);
        m_is_open = true;
    }
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account already closed");
    } else {
        /* Reset account state so that a subsequently reopened
         * account starts from a zero balance, as required by the
         * specification/tests. */
        m_is_open = false;
        m_balance = static_cast<std::int64_t>(0);
    }
}

void Bankaccount::deposit(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    } else if (amount < static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Cannot deposit negative amount");
    } else {
        m_balance += amount;
    }
}

void Bankaccount::withdraw(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    } else if (amount < static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Cannot withdraw negative amount");
    } else if (m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    } else {
        m_balance -= amount;
    }
}

std::int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    } else {
        return m_balance;
    }
}

}  // namespace Bankaccount
