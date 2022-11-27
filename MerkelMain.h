//The MerkelMain class represents the application itself, 
//and it deals with user input and menu printing. 

#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();  

    private: 
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterOffer();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        void processUserOption(int userOption);

        OrderBook orderBook{"20200317.csv"};

};