#include <bits/stdc++.h>
using namespace std;

class Account
{
private:
    int Account_no;
    string account_holder_name;
    double balance;

public:
    Account(int Account_no, string name, double balance)
    {
        this->Account_no = Account_no;
        this->account_holder_name = name;
        this->balance = balance;
    }

    int get_Account_No()
    {
        return Account_no;
    }
    string get_account_holder_name()
    {
        return account_holder_name;
    }
    double get_balance()
    {
        return balance;
    }

    bool deposit(double amount)
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

    virtual bool withdraw(double amount)
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

    void change_balance(double amount)
    {
        balance += amount;
    }

    void displayBalance()
    {
        cout << "Account Number : " << Account_no << endl;
        cout << "Account holder name : " << account_holder_name << endl;
        cout << "Balance : " << balance << endl;
    }
};

class Saving_Account : public Account
{
private:
    double interest_rate;

public:
    Saving_Account(int Account_no, string name, double balance, double rate) : Account(Account_no, name, balance)
    {
        this->interest_rate = rate;
    }

    void addInterest()
    {
        double interest = get_balance() * interest_rate / 100;
        if (deposit(interest))
        {
            cout << "The interest added is " << interest << endl;
            cout << "Current balance is " << get_balance() << endl;
        }
    }
};

class Current_Account : public Account
{
private:
    double over_draft_limit;

public:
    Current_Account(int Account_no, string name, double balance, double overdraft_limit) : Account(Account_no, name, balance)
    {
        this->over_draft_limit = overdraft_limit;
    }

    bool withdraw(double amount) override
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
};

class Bank
{
private:
    vector<Account *> accounts;
    int nextAccountnumber = 1001;

public:
    // Account Creation
    void create_saving_account(string name, double balance, double rate)
    {
        Account *acc = new Saving_Account(nextAccountnumber++, name, balance, rate);
        accounts.push_back(acc);
        cout << "Saving Account created " << endl;
    }
    void create_current_account(string name, double balance, double overdraft_limit)
    {
        Account *acc = new Current_Account(nextAccountnumber++, name, balance, overdraft_limit);
        accounts.push_back(acc);
        cout << "Current Account created " << endl;
    }

    // finding Account
    Account *find_acc(int account_no)
    {
        for (auto acc : accounts)
        {
            if (acc->get_Account_No() == account_no)
            {
                return acc;
            }
        }

        return NULL; // If no account found
    }

    void deposit_to_account(int account_no, int amount)
    {
        Account *acc = find_acc(account_no);
        if (acc != NULL)
        {
            if (acc->deposit(amount))
            {
                cout << "Your Amount was deposited. Current balance: " << acc->get_balance() << endl;
            }
            else
            {
                cout << "Amount failed to deposit " << endl;
            }
        }
        else
        {
            cout << "Account not found" << endl;
        }
    }
    void withdraw_from_account(int account_no, int amount)
    {
        Account *acc = find_acc(account_no);
        if (acc != NULL)
        {
            if (acc->withdraw(amount))
            {
                cout << "Your amount was debited. Current balance:  " << acc->get_balance() << endl;
            }
            else
            {
                cout << "transaction failed " << endl;
            }
        }
        else
        {
            cout << "Account not found" << endl;
        }
    }

    void transaction_between_accounts(int from_account_no, int to_account_no, int amount)
    {
        Account *acc1 = find_acc(from_account_no);
        Account *acc2 = find_acc(to_account_no);
        if (acc1 != NULL && acc2 != NULL)
        {
            if (acc1->withdraw(amount))
            {
                if (acc2->deposit(amount))
                {
                    cout << "Transaction completed succesfull" << endl;
                }
                else{
                    acc1->deposit(amount);
                    cout<<"Transacrion failed  as deposit failed so withdrwal rolled back "<<endl ;
                }
            }
        }
        else
        {
            cout << "Transaction failed" << endl;
        }
    }

    void displayAllAccounts()
    {
        for (auto acc : accounts)
        {
            acc->displayBalance();
            cout << "--------------------" << endl;
        }
    }
};

int main()
{
    Bank bank;
    int choice;

    bank.create_saving_account("Kris",8000,5);
    bank.withdraw_from_account(1001 , 3000);
    bank.deposit_to_account(1001,5000);
    bank.create_current_account("John", 3000, 3000);
    bank.withdraw_from_account(1002, 5000);
    bank.transaction_between_accounts(1001,1002,3000);
    bank.displayAllAccounts();

    // do {
    //     cout << "\n--- Bank Menu ---\n";
    //     cout << "1. Create Savings Account\n";
    //     cout << "2. Create Current Account\n";
    //     cout << "3. Deposit\n";
    //     cout << "4. Withdraw\n";
    //     cout << "5. Display Account\n";
    //     cout << "6. Display All Accounts\n";
    //     cout << "0. Exit\n";
    //     cout << "Enter choice: ";
    //     cin >> choice;

    //     int accNum;
    //     string name;
    //     double amount, rate, limit;

    //     switch(choice) {
    //         case 1:
    //             cout << "Enter Name: ";
    //             cin >> ws;
    //             getline(cin, name);
    //             cout << "Initial Deposit: ";
    //             cin >> amount;
    //             cout << "Interest Rate (%): ";
    //             cin >> rate;
    //             bank.create_saving_account(name, amount, rate);
    //             break;

    //         case 2:
    //             cout << "Enter Name: ";
    //             cin >> ws;
    //             getline(cin, name);
    //             cout << "Initial Deposit: ";
    //             cin >> amount;
    //             cout << "Overdraft Limit: ";
    //             cin >> limit;
    //             bank.create_current_account(name, amount, limit);
    //             break;

    //         case 3:
    //             cout << "Enter Account Number: ";
    //             cin >> accNum;
    //             cout << "Enter Amount to Deposit: ";
    //             cin >> amount;
    //             if(bank.find_acc(accNum))
    //                 bank.find_acc(accNum)->deposit(amount);
    //             else
    //                 cout << "Account not found!" << endl;
    //             break;

    //         case 4:
    //             cout << "Enter Account Number: ";
    //             cin >> accNum;
    //             cout << "Enter Amount to Withdraw: ";
    //             cin >> amount;
    //             if(bank.find_acc(accNum))
    //                 bank.find_acc(accNum)->withdraw(amount);
    //             else
    //                 cout << "Account not found!" << endl;
    //             break;

    //         case 5:
    //             cout << "Enter Account Number: ";
    //             cin >> accNum;
    //             if(bank.find_acc(accNum))
    //                 bank.find_acc(accNum)->displayBalance();
    //             else
    //                 cout << "Account not found!" << endl;
    //             break;

    //         case 6:
    //             bank.displayAllAccounts();
    //             break;

    //         case 0:
    //             cout << "Exiting...\n";
    //             break;

    //         default:
    //             cout << "Invalid choice!\n";
    //     }

    // } while(choice != 0);

    return 0;
}
