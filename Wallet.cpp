#include "Wallet.h"

Wallet::Wallet()
{

}

void Wallet::insertCurrency(std::string type, double amount)
{
    double balance;
    if (amount < 0)
    {
        throw std::exception{};
    }
    if (currencies.count(type) == 0) //not there yet
    {
        balance = 0;
    }
    else { //is there
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
    double balance;
    if (amount < 0)
    {
        return false;
    }
    if (currencies.count(type) == 0) //no currency of this type
    {
        return false;
    }
    else { //currency is there - do we have enough?
        if (containsCurrency(type, amount))// we know there is enough
        {
            currencies[type] -= amount;
            return true;
        }
        else 
            return false; //they have the currency but not enough
    }
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    if (currencies.count(type) == 0) 
        return false;
    else 
        return currencies[type] >= amount;
}

std::string Wallet::toString()
{
    std::string s;
    
    for (std::pair<std::string,double> pair : currencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n"; 
    }
    return s;
}