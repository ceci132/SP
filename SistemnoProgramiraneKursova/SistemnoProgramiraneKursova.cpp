// SistemnoProgramiraneKursova.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <stdlib.h>
#include <thread>
#include <cmath>
#include <random>

using namespace std;

map<string, double> menu = {
    {"Orange", 0.7},
    {"Water", 0.6},
    {"Bread", 1.1},
    {"Coffee", 1.3},
    {"Tea", 0.8},
    {"Milk", 2.9},
    {"Ham", 6.7},
    {"Meat", 12.7},
    {"Oil", 6.6},
    {"Rise", 4.6},
    {"CocaCola", 2.3},
    {"Chips", 3},
    {"Beans", 1.5},
    {"Salt", 2.0},
    {"Hamburger", 3.6},
    {"HotDog", 2},
    {"Biscuits", 2.7},
    {"Shtrudel", 6},
    {"Donut", 1.3},
    {"Pizza", 2.8},
    {"Shampoo", 5.6},
    {"Vodka", 78.6},
    {"Whiskey", 47.8} };

double currency[]{ 0.10, 0.20, 0.50, 1, 2, 5, 10, 20, 50, 100 };

map<double, int> stock = {
    {0.10, 100},
    {0.20, 100},
    {0.50, 50},
    {1, 50},
    {2, 50},
    {5, 25},
    {10, 25},
    {20, 25},
    {50, 25},
    {100, 10} };

map<double, int> get_money(int quantity)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::poisson_distribution<> distribution(4);

    std::map<double, int> hist;
    for (int n = 0; n < quantity; ++n)
    {
        int number = distribution(generator);
        if (number < 10)
            ++hist[currency[number]];
    }
    return hist;
}

void buy(std::map<string, double>::iterator product, std::map<double, int> cash)
{
    auto& [name, product_price] = *product;
    double client_money = 0;
    for (auto& [curr, quantity] : cash){
        client_money += curr * quantity;
    }
    cout << endl << "Trying to buy " << name << " for " << product_price << " with " << client_money << endl;
    if (client_money < product_price){
        cout << "Client has insufficient money..." << endl;
        return;
    }
    for (auto& [curr, quantity] : cash){
        stock[curr] += quantity;
    }
    double change = client_money - product_price;

    cout << "Expected change: " << change << endl;

    for (auto s = stock.rbegin(); s != stock.rend(); ++s){
        auto& [curr, quantity] = *s;

        while (change - curr >= 0){
            if (quantity < 1){
                break;
            }

            quantity -= 1;
            change -= curr;
            cout << "- using a '" << curr << "'" << endl;
        }
    }
}

void sim()
{
    int i = 0;
    while (i < 50)
    {
        auto product = menu.begin();
        std::advance(product, rand() % menu.size());

        auto cash = get_money(6);
        buy(product, cash);
        i++;
    }
    cout << "Leftover currency:" << endl;
    cout << "------------------" << endl;
    for (const auto& [curr, quant] : stock)
    {
        cout << curr << " : " << quant << endl;
    }
    cout << "------------------" << endl;
}

int main()
{
    thread x(sim);
    x.join();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
