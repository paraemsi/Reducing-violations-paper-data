#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : current_balance(0), is_closed(true) {
}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_closed) {
        throw std::runtime_error("Account is already open");
    }
    is_closed = false;
    current_balance = 0;
}

void Bankaccount::deposit(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_closed) {
        throw std::runtime_error("Account is closed");
    }
    if ((amount <= 0)) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    current_balance += amount;
}

void Bankaccount::withdraw(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_closed) {
        throw std::runtime_error("Account is closed");
    }
    if ((amount <= 0)) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    if ((amount > current_balance)) {
        throw std::runtime_error("Insufficient funds");
    }
    current_balance -= amount;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_closed) {
        throw std::runtime_error("Account is already closed");
    }
    is_closed = true;
}

std::int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_closed) {
        throw std::runtime_error("Account is closed");
    }
    return current_balance;
}

}  // namespace Bankaccount
