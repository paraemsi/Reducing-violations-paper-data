#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <optional>
#include <stdexcept>

namespace Bankaccount {

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();

    void open();
    void close();
    void deposit(int amount);
    void withdraw(int amount);
    int balance();

private:
    mutable std::mutex mtx_;
    bool is_open_;
    int balance_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
