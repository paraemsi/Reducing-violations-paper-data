#include "bank_account.h"
#include <stdexcept>
#include <mutex>

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

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Invalid amount");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Invalid amount");
    }
    if (amount > m_balance) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    m_is_open = false;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
