//The MerkelMain class represents the application itself, 
//and it deals with user input and menu printing. 

#include "MerkelMain.h"
#include <iostream>
#include <vector> 
#include "OrderBookEntry.h"
#include "CSVReader.h"

bool show_main_menu = true;

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10.0);

    while(true)
    {
        if(show_main_menu)
        {
            printMenu();
        }
        
        input = getUserOption();
        processUserOption(input);
    }
}

// void MerkelMain::loadOrderBook()
// {
    
//     // orders = CSVReader::readCSV("20200317.csv");

// }

void MerkelMain::printMenu()
{
    std::cout << "============================ " << std::endl;
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print market stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an ask " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue   
    std::cout << "6: Continue " << std::endl;
    // 7 advisorbot    
    std::cout << "7: Use Advisorbot" << std::endl;
    
    std::cout << "============================ " << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void  MerkelMain::printMarketStats()
{
    for(std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(  OrderBookType::ask, 
                                                                    p, 
                                                                    currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;

    }
    
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product, price, amount, eg. ETH/BTC,200,0.5" << std::endl;
    std::string input;
    
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "Bad input! " << input << std::endl;
    }
    else {
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Insuficient funds." << std::endl;
            }
            
        }catch (const std::exception& e)
        {
            std::cout << "MerkelMain::enterAsk Bad input!" << std::endl;
        }
    }

    std::cout << "You typed: " << input << std::endl;

}

void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount: product, price, amount, eg. ETH/BTC,200,0.5" << std::endl;
    std::string input;
    
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Insuficient funds." << std::endl;
            }
            
        }catch (const std::exception& e)
        {
            std::cout << "MerkelMain::enterBid Bad input!" << std::endl;
        }
    }

    std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    std::cout << "Sales: " << sales.size() << std::endl;
    for (OrderBookEntry& sale : sales)
    {
        std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
        if(sale.username == "simuser")
        {
            wallet.processSale(sale);
            
        }

    }
    currentTime = orderBook.getNextTime(currentTime);
}
 
int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;

    std::cout << "Type in 1-7" << std::endl;
    std::getline(std::cin, line);
    
    try{
        userOption = std::stoi(line);

    }catch(const std::exception& e)
    {
        //
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}


void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-7 or Advisorbot commands" << std::endl;
    }
    if (userOption == 1) 
    {
        printHelp();
    }
    if (userOption == 2) 
    {
        printMarketStats();
    }
    if (userOption == 3) 
    {
        enterAsk();
    }
    if (userOption == 4) 
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        gotoNextTimeframe();
    }
    if (userOption == 7)
    {
        runAdvisorbot();
        show_main_menu = false;
    }
}

int MerkelMain::runAdvisorbot()
{
    // Enable the Advisorbot menu
    
    std::cout << "==========Advisorbot========== " << std::endl;
    std::cout << "advisorbot> Welcome to Advisorbot" << std::endl;
    std::cout << "advisorbot> Please enter a command, or help for a list of commands" << std::endl;
    std::string input;
    std::cin >> input;
    std::cout << "==========Advisorbot========== " << std::endl;

    if (input == "help") 
    {
        std::cout << "help <cmd>    | Displays help for a specific command." << std::endl;
        std::cout << "prod          | Displays a list of all available products on the currency exchange." << std::endl;
        std::cout << "min           | Finds the minimum bid or ask for the product in the current time step." << std::endl;
        std::cout << "max           | Finds the maximum bid or ask for the product in the current time step." << std::endl;
        std::cout << "avg           | Computes the average ask or bid for the selected product over the selected number of timesteps." << std::endl;
        std::cout << "predict       | Predicts the minimum or maximum ask or bid for the sent product for the next time step." << std::endl;
        std::cout << "time          | States the current time step in the dataset of the currency exchange." << std::endl;
        std::cout << "step          | Move to the next time step of the dataset." << std::endl;
    } 
    else if (input == "help <cmd>") 
    {
        //do something
    } 
    else if (input == "prod") 
    {
        //do something
    } 
    else if (input == "min") 
    {
        //do something
    } 
    else if (input == "max") 
    {
        //do something
    } 
    else if (input == "avg") 
    {
        //do something
    } 
    else if (input == "predict") 
    {
        //do something
    } 
    else if (input == "time") 
    {
        //do something
    } 
    else if (input == "step") 
    {
        //do something
    } 
    else 
    {
        //do something
    }

  return 0;
}