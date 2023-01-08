#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"



class BotCalculations
{
    public:
        BotCalculations();

        std::string getProducts();
        
        int getMinimum();
        int getMaximum();

        //getAverage();

        //getPrediction();

    private: 
    

};


