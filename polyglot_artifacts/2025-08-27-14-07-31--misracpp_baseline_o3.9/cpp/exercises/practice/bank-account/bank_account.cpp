#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() = default;

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_open) {
        throw std::runtime_error("account already open");
    }
    m_open = true;
    m_balance = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account already closed");
    }
    m_open = false;
    m_balance = 0;  // reset balance when account is closed
}

int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account is closed");
    }
    return m_balance;
}

void Bankaccount::deposit(int64_t amount) {
    if (amount <= 0) {
        throw std::runtime_error("deposit amount must be positive");
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account is closed");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(int64_t amount) {
    if (amount <= 0) {
        throw std::runtime_error("withdraw amount must be positive");
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account is closed");
    }
    if (m_balance < amount) {
        throw std::runtime_error("insufficient funds");
    }
    m_balance -= amount;
}

}  // namespace Bankaccount
