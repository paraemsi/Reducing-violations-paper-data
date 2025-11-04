#include "bank_account.h"
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : m_open(false), m_balance(0) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_open) {
        throw std::runtime_error("account already open");
    }
    m_balance = 0;
    m_open = true;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account not open");
    }
    m_open = false;
    m_balance = 0;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account not open");
    }
    return m_balance;
}

void Bankaccount::deposit(int amount) {
    if (amount < 0) {
        throw std::runtime_error("negative deposit");
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account not open");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(int amount) {
    if (amount < 0) {
        throw std::runtime_error("negative withdrawal");
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("account not open");
    }
    if (amount > m_balance) {
        throw std::runtime_error("insufficient funds");
    }
    m_balance -= amount;
}

}  // namespace Bankaccount
