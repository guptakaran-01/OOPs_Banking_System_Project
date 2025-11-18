#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

struct Transaction
{
    std::string time;          
    std::string type;         
    double amount;            
    double final_balance;    
};

#endif
