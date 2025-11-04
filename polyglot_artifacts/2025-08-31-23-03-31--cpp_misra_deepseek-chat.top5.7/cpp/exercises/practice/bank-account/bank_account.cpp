#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : m_balance(0), m_is_open(false) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (m_is_open) {
        throw std::runtime_error("Account already open");
    }
    m_is_open = true;
    m_balance = 0;
}

void Bankaccount::deposit(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

std::int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    return m_balance;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account is not open");
    }
    m_is_open = false;
}

}  // namespace Bankaccount
