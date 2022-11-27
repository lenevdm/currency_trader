//The OrderBook class presents a high level interface on all the orders 
//in the order book data set, including query functions to find out which products 
//are in the data set, and to retrieve a subset of the orders using filters.

#include "OrderBook.h"
#include "CSVReader.h"
#include <map>




OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);

}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;

    for(OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }

    for (auto const& e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(  OrderBookType type, 
                                        std::string product,
                                        std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    return orders_sub;
}