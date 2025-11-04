#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <optional>

namespace Bankaccount {

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();

    void open();
    void close();
    int balance();
    void deposit(int amount);
    void withdraw(int amount);

private:
    std::mutex mtx_;
    bool is_open_;
    int balance_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
