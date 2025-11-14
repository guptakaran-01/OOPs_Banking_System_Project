#include "Account.h" 
#include <bits/stdc++.h>
using namespace std;

Account::Account(int Account_no, string name, double balance)
{
    this->Account_no = Account_no;
    this->account_holder_name = name;
    this->balance = balance;
}

void Account::setname(string name)
{
    this->account_holder_name = name;
}

int Account::get_Account_No()
{
    return Account_no;
}
string Account::get_account_holder_name()
{
    return account_holder_name;
}
double Account::get_balance()
{
    return balance;
}

bool Account::deposit(double amount)
{
    if (amount > 0)
    {
        balance += amount;
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

void Account::displayBalance()
{
    cout << "Account Number : " << Account_no << endl;
    cout << "Account holder name : " << account_holder_name << endl;
    cout << "Balance : " << balance << endl;
}

Saving_Account::Saving_Account(int Account_no, string name, double balance, double rate) : Account(Account_no, name, balance)
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

Current_Account::Current_Account(int Account_no, string name, double balance, double overdraft_limit) : Account(Account_no, name, balance)
{
    this->over_draft_limit = overdraft_limit;
}

bool Current_Account::withdraw(double amount) 
{
    if (amount > 0 && amount <= get_balance() + over_draft_limit)
    {
        Account::change_balance(-amount);
        return true;
    }
    else
    {
        return false;
    }
}
