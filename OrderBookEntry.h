//The OrderBookEntry represents a row in the order book data set 
//(i.e. a single order in the order book). 
//It can be a bid or an ask order.

#pragma once

#include <string>

enum class OrderBookType{bid, ask, unknown};

class OrderBookEntry
{
    public:
        //Constructor
        OrderBookEntry( double _price,
                        double _amount,
                        std::string _timestamp,
                        std::string _product,
                        OrderBookType _orderType);
        static OrderBookType stringToOrderBookType(std::string s);

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType; 

};
