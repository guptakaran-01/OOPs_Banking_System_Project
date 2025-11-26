#include "Account.h"
#include <iostream>
#include <fstream>
using namespace std;

Account::Account(int Account_no, const string &name, double balance)
{
    this->Account_no = Account_no;
    this->account_holder_name = name;
    this->balance = balance;
}

Account::~Account()
{
}

void Account::setname(const string& name)
{
    this->account_holder_name = name;
}

int Account::get_Account_No() const
{
    return Account_no;
}
string Account::get_account_holder_name() const
{
    return account_holder_name;
}
double Account::get_balance() const
{
    return balance;
}

bool Account::deposit(double amount)
{
    if (amount > 0)
    {
        balance += amount;
        record_transaction("Deposit", amount);
        return true;
    }
    else
    {
        return false;
    }
}

bool Account::withdraw(double amount)
{
    if (amount > 0 && amount <= balance)
    {
        balance -= amount;
        record_transaction("withdraw", amount);
        return true;
    }
    else
    {
        return false;
    }
}

void Account::change_balance(double amount)
{
    balance += amount;
}

void Account::displayBalance() const
{
    cout << "Account Number : " << Account_no << endl;
    cout << "Account holder name : " << account_holder_name << endl;
    cout << "Balance : " << balance << endl;
}

void Account::record_transaction(const string &type, double amount)
{
    // converting time in human readable format
    time_t now = time(0);   // current system time
    char *dt = ctime(&now); // convert to string (includes newline)

    string time_str(dt);
    time_str.pop_back();

    Transaction tr;
    tr.time = time_str;
    tr.type = type;
    tr.amount = amount;
    tr.final_balance = get_balance();

    transactions.push_back(tr);
}
void Account::print_transaction_history() const
{
    cout << "Transaction history" << endl;
    for (const auto &tr : transactions)
    {
        cout << tr.time << " | " << tr.type << " | " << tr.amount << " | Balance : " << tr.final_balance << endl;
    }
}

Saving_Account::Saving_Account(int Account_no, const string &name, double balance, double rate) : Account(Account_no, name, balance)
{
    this->interest_rate = rate;
}

bool Saving_Account::addInterest()
{
    double interest = get_balance() * interest_rate / 100;
    if (deposit(interest))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Current_Account::Current_Account(int Account_no, const string &name, double balance, double overdraft_limit) : Account(Account_no, name, balance)
{
    this->over_draft_limit = overdraft_limit;
}

bool Current_Account::withdraw(double amount)
{
    if (amount > 0 && amount <= get_balance() + over_draft_limit)
    {
        Account::change_balance(-amount);
        record_transaction("Withdraw", amount);
        return true;
    }
    else
    {
        return false;
    }
}

void Account::exportHistory(const string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file name" << filename << endl;
        return;
    }

    file << "Account NO " << Account_no << "\n";
    file << "Account holder name " << account_holder_name << "\n";

    file << "-----------------------\n";
    file << "Transaction history :\n";
    if (transactions.empty())
    {
        file << "No transaction available\n";
    }
    else
    {
        for (const auto &tr : transactions)
        {
            file << tr.time << " | " << tr.type
                 << " | Amount: " << tr.amount
                 << " | Balance: " << tr.final_balance << "\n";
        }
    }
    file << "---------------------------------\n";
    file << "END OF REPORT\n";

    file.close();
    cout << "Transaction history exported to: " << filename << endl;
}