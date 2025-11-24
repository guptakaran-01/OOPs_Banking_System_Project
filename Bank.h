#ifndef BANK_H
#define BANK_H
#include "IAccount.h" 
#include "Account.h" 
#include <vector>
#include <string>


class Bank
{
private:
    std::vector<IAccount *> accounts;
    int nextAccountnumber = 1001;

public:
    void create_saving_account(const std::string& name, double balance, double rate);
    void create_current_account(const std::string& name, double balance, double overdraft_limit);
    IAccount *find_acc(int account_no);
    std::vector<IAccount*> find_acc_by_name(const std::string& name);
    void deposit_to_account(int account_no, double amount);
    void withdraw_from_account(int account_no, double amount);
    void transaction_between_accounts(int from_account_no, int to_account_no, double amount);
    void close_account(int account_no);
    void Edit_Account_Details(int account_no, const std::string& new_name);
    void Auto_generate_saving_interest();
    void Minimum_balace_Warning();
    void displayAllAccounts();
    void auto_generate_report();
    void print_account_history(int account_no);
    void export_account_history(int account_no, const std::string& filename);

     
};

#endif