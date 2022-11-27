//The OrderBook class presents a high level interface on all the orders 
//in the order book data set, including query functions to find out which products 
//are in the data set, and to retrieve a subset of the orders using filters.

#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
    public:
    /** construct, reading a csv data file */
        OrderBook(std::string filename);
    /** return vector of all known products in the dataset */
        std::vector<std::string> getKnownProducts();
    /** return vector of Orders according to the sent filters */
        std::vector<OrderBookEntry> getOrders(  OrderBookType type, 
                                                std::string product,
                                                std::string timestamp);

        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        static double getLowPrice(std::vector<OrderBookEntry>& orders);

    private:
        std::vector<OrderBookEntry> orders;

};