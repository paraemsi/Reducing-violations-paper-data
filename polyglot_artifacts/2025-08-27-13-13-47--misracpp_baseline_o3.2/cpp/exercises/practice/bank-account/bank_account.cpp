#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mutex_);
    if (m_open_) {
        return;
    }
    m_balance_ = 0;
    m_open_ = true;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mutex_);
    if (!m_open_) {
        throw std::runtime_error("account closed");
    }
    m_open_ = false;
    m_balance_ = 0;
}

void Bankaccount::deposit(int amount) {
    if (amount < 0) {
        throw std::runtime_error("negative deposit not allowed");
    }
    std::lock_guard<std::mutex> lock(m_mutex_);
    if (!m_open_) {
        throw std::runtime_error("account closed");
    }
    m_balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    if (amount < 0) {
        throw std::runtime_error("negative withdraw not allowed");
    }
    std::lock_guard<std::mutex> lock(m_mutex_);
    if (!m_open_) {
        throw std::runtime_error("account closed");
    }
    if (m_balance_ < amount) {
        throw std::runtime_error("insufficient funds");
    }
    m_balance_ -= amount;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mutex_);
    if (!m_open_) {
        throw std::runtime_error("account closed");
    }
    return m_balance_;
}

}  // namespace Bankaccount
