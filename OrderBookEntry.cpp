//The OrderBookEntry represents a row in the order book data set 
//(i.e. a single order in the order book). 
//It can be a bid or an ask order.

#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry( double _price,
                        double _amount,
                        std::string _timestamp,
                        std::string _product,
                        OrderBookType _orderType)
// Initializer list
: price(_price), 
  amount(_amount), 
  timestamp(_timestamp),
  product(_product),
  orderType(_orderType)
{
    
}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
  if (s == "ask")
  {
    return OrderBookType::ask;
  }
  if (s == "bid")
  {
    return OrderBookType::bid;
  }
  if (s == "sale")
  {
    return OrderBookType::sale;
  }
  return OrderBookType::unknown;
}