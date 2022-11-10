#include <iostream>
#include <string>
#include <vector>

void printMenu()
{
    // 1 Print help
    std::cout << "1. Print help " << std::endl;
    // 2 Print exchange stats
    std::cout << "2. Print exchange stats " << std::endl;
    // 3 Make an offer
    std::cout << "3. Make an offer " << std::endl;
    // 4 Make a bid
    std::cout << "4. Make a bid " << std::endl;
    // 5 Print wallet
    std::cout << "5. Print wallet " << std::endl;
    // 6 Continue
    std::cout << "6. Continue " << std::endl;

    
    std::cout << "===================" << std::endl;
    std::cout << "Type in 1-6." << std::endl;
    
}

// Menu functions
void printHelp()
{
    std::cout << "Your aim is to make money, analyze the market and make bids and offers." << std::endl;
}

void printMarketStats()
{
    std::cout << "Market looks good." << std::endl;
}

void enterOffer()
{
    std::cout << "Make an offer - enter the amount." << std::endl;
}

void enterBid()
{
    std::cout << "Make a bid - enter the amount." << std::endl;
}

void printWallet()
{
    std::cout << "Your wallet is empty." << std::endl;
}

void gotoNextTimeFrame()
{
    std::cout << "Going to next timeframe." << std::endl;
}

int getUserOption()
{
    int userOption;
    std::cin >> userOption;
    std::cout << "You chose: " <<  userOption << std::endl;
    return userOption;
}

void processUserOption(int userOption)
{
    if (userOption == 0) // Bad input
    {
        std::cout << "Invalid choice. Choose 1-6." << std::endl;
    }
    if (userOption == 1) // 1 Print help
    {
        printHelp();
    }
    if (userOption == 2) // 2 Print exchange stats
    {
        printMarketStats();
    }
    if (userOption == 3) // 3 Make an offer
    {
        enterOffer();
    }
    if (userOption == 4) // 4 Make a bid
    {
        enterBid();
    }
    if (userOption == 5) // 5 Print wallet
    {
        printWallet();
    }
    if (userOption == 6) // 6 Continue
    {
        gotoNextTimeFrame();
    }
}

int main()
{
    //Representing one entry in the order book
    // double price = 5319.450228;
    // double amount = 0.00020075;
    // std::string timestamp{"2020/03/17 17:01:24.884492"};
    // std::string product{"BTC/USDT"};
    enum class OrderBookType{bid, ask};

    //Representing multiple order book entries using vectors
    std::vector<double> prices;
    std::vector<double> amounts;
    std::vector<std::string> timestamps;
    std::vector<std::string> products;
    std::vector<OrderBookType> orderTypes;
    
    //Add data to vectors using push_back
    prices.push_back(500.01);
    amounts.push_back(0.001);
    timestamps.push_back("2020/03/17 17:01:24.88449");
    products.push_back("BTC/USDT");
    orderTypes.push_back(OrderBookType::bid);

    prices.push_back(1000.01);
    amounts.push_back(0.001);
    timestamps.push_back("2020/03/17 17:01:24.88449");
    products.push_back("BTC/USDT");
    orderTypes.push_back(OrderBookType::ask);

    //Accessing data in the vectors
    std::cout <<"prices: " << prices[0] << std::endl;
    std::cout <<"prices: " << prices[1] << std::endl;

    // while(true)
    // {
    //     printMenu();

    //     int userOption = getUserOption();

    //     processUserOption(userOption);
    // }
    
    return 0;
    

}