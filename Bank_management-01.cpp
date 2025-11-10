#include <bits/stdc++.h>
using namespace std ;


class Account {
    private:
    int Account_no;
    string account_holder_name ;
    double balance;

    public:

    Account (int Account_no , string name , double balance){
        this->Account_no=Account_no;
        this->account_holder_name=name;
        this->balance=balance;
    }

   int get_Account_No(){
    return Account_no;
   }
   string get_account_holder_name(){
    return account_holder_name;
   }
   double  get_balance(){
    return balance;
   }

   void deposit (double amount){
    if(amount>0){
        balance+=amount;
        cout<<"Deposited : "<<amount<<" Current balance : "<<balance<<endl;
    }
    else{
        cout<<"Invalid Amount"<<endl;

    }
   }

  virtual void withdraw(double amount){
    if(amount >0 && amount <=balance){
        balance-=amount;
        cout<<"Withdrawn :"<<amount<<endl;
    }
    else{
        cout<<"Insufficient balance or invalid amount"<<endl;
    }
  }

  void displayBalance(){
    cout<<"Account Number : "<<Account_no<<endl;
    cout<<"Account holder name : "<<account_holder_name<<endl;
    cout<<"Balance : "<<balance<<endl;
  }


};

class Saving_Account : public Account {
   private:
   double interest_rate;

   public:
   Saving_Account(int Account_no , string name , double balance , double rate) : Account(Account_no ,  name , balance){
    this->interest_rate=rate;
   }

   void addInterest(){
    double interest= get_balance()*interest_rate/100;
    deposit(interest);
    cout<<"The interest added is "<<interest<<endl;
    cout<<"Current balance is "<<get_balance()<<endl;
   }
};

class Current_Account :public Account {
    private:
    double over_draft_limit;

    public:
    Current_Account(int Account_no , string name , double balance , double overdraft_limit): Account(Account_no ,  name , balance){
        this->over_draft_limit=overdraft_limit;
    }

     void withdraw(double amount) override{
        if(amount>0 && amount<= get_balance()+over_draft_limit){
            double new_balance=get_balance()-amount;
           Account:: withdraw(amount);
           cout<<"Amount withdrawn : "<<amount<<endl;
           cout<<"Current balance : "<<new_balance<<endl;
        }
        else{
            cout<<" Exceeded overdraft limit or invalid amount"<<endl;
        }
     }
};



class Bank{
    private:
    vector<Account*>accounts;
    int nextAccountnumber =1001; 

    public:

    //Account Creation
    void create_saving_account(string name , double balance , double rate){
        Account* acc= new Saving_Account(nextAccountnumber++ , name , balance ,rate);
        accounts.push_back(acc);
        cout<<"Saving Account created "<<endl;
    }
    void create_current_account(string name , double balance , double overdraft_limit){
        Account* acc= new Current_Account(nextAccountnumber++ , name , balance ,overdraft_limit);
        accounts.push_back(acc);
        cout<<"Current Account created "<<endl;
    }


    // finding Account 
    Account* find_acc(int account_no){
        for(auto acc : accounts){
            if(acc->get_Account_No()==account_no){
                return acc;
            }
        }
       
       return NULL; // If no account found 
        
    }

     
    void displayAllAccounts(){
        for(auto acc: accounts){
            acc->displayBalance();
            cout<<"--------------------"<<endl;
        }
    }
};



int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n--- Bank Menu ---\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Current Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Display Account\n";
        cout << "6. Display All Accounts\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int accNum;
        string name;
        double amount, rate, limit;

        switch(choice) {
            case 1:
                cout << "Enter Name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Initial Deposit: ";
                cin >> amount;
                cout << "Interest Rate (%): ";
                cin >> rate;
                bank.create_saving_account(name, amount, rate);
                break;

            case 2:
                cout << "Enter Name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Initial Deposit: ";
                cin >> amount;
                cout << "Overdraft Limit: ";
                cin >> limit;
                bank.create_current_account(name, amount, limit);
                break;

            case 3:
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Amount to Deposit: ";
                cin >> amount;
                if(bank.find_acc(accNum))
                    bank.find_acc(accNum)->deposit(amount);
                else
                    cout << "Account not found!" << endl;
                break;

            case 4:
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Amount to Withdraw: ";
                cin >> amount;
                if(bank.find_acc(accNum))
                    bank.find_acc(accNum)->withdraw(amount);
                else
                    cout << "Account not found!" << endl;
                break;

            case 5:
                cout << "Enter Account Number: ";
                cin >> accNum;
                if(bank.find_acc(accNum))
                    bank.find_acc(accNum)->displayBalance();
                else
                    cout << "Account not found!" << endl;
                break;

            case 6:
                bank.displayAllAccounts();
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 0);

    return 0;
}
