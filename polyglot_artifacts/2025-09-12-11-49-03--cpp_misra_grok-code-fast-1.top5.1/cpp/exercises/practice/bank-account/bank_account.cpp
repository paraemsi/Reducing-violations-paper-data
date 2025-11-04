#include "bank_account.h"

namespace Bankaccount {

Bankaccount::Bankaccount() : is_open(false), balance(0) {}

bool Bankaccount::open() {
    std::lock_guard<std::mutex> guard(mtx);
    if (!is_open) {
        is_open = true;
        balance = 0;
        return true;
    }
    return false;
}

bool Bankaccount::close() {
    std::lock_guard<std::mutex> guard(mtx);
    if (is_open) {
        is_open = false;
        return true;
    }
    return false;
}

bool Bankaccount::deposit(std::int64_t amount) {
    if (amount <= 0) {
        return false;
    }
    std::lock_guard<std::mutex> guard(mtx);
    if (is_open) {
        balance = (balance + amount);
        return true;
    }
    return false;
}

bool Bankaccount::withdraw(std::int64_t amount) {
    if (amount <= 0) {
        return false;
    }
    std::lock_guard<std::mutex> guard(mtx);
    if ((is_open) && ((balance - amount) >= 0)) {
        balance = (balance - amount);
        return true;
    }
    return false;
}

std::int64_t Bankaccount::balance() {
    std::lock_guard<std::mutex> guard(mtx);
    if (is_open) {
        return balance;
    } else {
        throw std::runtime_error("Account is closed");
    }
}

}  // namespace Bankaccount
